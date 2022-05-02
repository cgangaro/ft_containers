#ifndef MAP_HPP
# define MAP_HPP

#include "../iterators/utils.hpp"
#include "../iterators/BSTNode.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key 														key_type;
			typedef T 															mapped_type;
			typedef ft::pair<const key_type,mapped_type> 						value_type;
			typedef Compare 													key_compare;
			typedef Alloc 														allocator_type;
			typedef typename allocator_type::reference 							reference;
			typedef typename allocator_type::const_reference 					const_reference;
			typedef typename allocator_type::pointer 							pointer;
			typedef typename allocator_type::const_pointer 						const_pointer;
			typedef BSTNode<value_type>											map_node;
			typedef ft::bidirectionnal_iterator<map_node, value_type>						iterator;
			typedef ft::const_bidirectionnal_iterator<map_node, const value_type, iterator>	const_iterator;
			typedef ft::reverse_iterator<iterator> 							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef std::ptrdiff_t 												difference_type;
			typedef size_t 														size_type;
			typedef typename Alloc::template rebind<map_node>::other			node_allocator_type;

		private:
			key_compare			_compare;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			map_node			*_root;
			map_node			*_end;
			map_node			*_begin;
			size_type			_size;

		public:

			class value_compare
			{
				friend class map;

				protected:

					Compare comp;

					value_compare(Compare c): comp(c)
					{

					}

				public:

					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool operator()(const value_type &x, const value_type &y) const
					{
						return (comp(x.first, y.first));
					}
			};

		map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _compare(comp), _alloc(alloc), _node_alloc(std::allocator<map_node>()), _root(NULL), _end(NULL), _begin(NULL), _size(0)
		{
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, map_node());

			_begin = _node_alloc.allocate(1);
			_node_alloc.construct(_begin, map_node());
			_begin->parent = _end;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _compare(comp), _alloc(alloc), _node_alloc(std::allocator<map_node>()), _root(NULL), _size(0)
		{
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, map_node());

			_begin = _node_alloc.allocate(1);
			_node_alloc.construct(_begin, map_node());
			_begin->parent = _end;
			insert(first, last);
		}

		map(const map &x): _compare(x._compare), _alloc(x._alloc), _node_alloc(x._node_alloc), _root(NULL), _size(0)
		{
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, map_node());

			_begin = _node_alloc.allocate(1);
			_node_alloc.construct(_begin, map_node());

			_begin->parent = _end;
			clear();

			this->insert(x.begin(), x.end());
		}

		~map()
		{
			clear();
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
			_node_alloc.destroy(_begin);
			_node_alloc.deallocate(_begin, 1);
		}

		map& operator=(const map& x)
		{
			clear();
			_compare = x._compare;
			_size = 0;
			_alloc = x._alloc;
			_node_alloc = x._node_alloc;
			insert(x.begin(), x.end());
			return (*this);
		}

		//Iterators

		iterator begin()
		{
			return (iterator(_begin->parent));
		}

		const_iterator begin() const
		{
			return (const_iterator(_begin->parent));
		}

		iterator end()
		{
			return (iterator(_end));
		}

		const_iterator end() const
		{
			return (const_iterator(_end));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(_end));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(_end));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_begin->parent));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_begin->parent));
		}

		//Capacity

		bool empty() const
		{
			if (_size == 0)
				return (true);
			return (false);
		}

		size_type size() const
		{
			return (_size);
		}

		size_type max_size() const
		{
			return (std::numeric_limits<size_type>::max() / sizeof(map_node));
		}

		//Observers

		key_compare key_comp() const
		{
			return (_compare);
		}

		value_compare value_comp() const
		{
			return (value_compare(_compare));
		}

		//Element access

		mapped_type& operator[](const key_type& k)
		{
			return (*(this->insert(value_type(k, mapped_type())).first)).second;
		}

		//Modifiers

		pair<iterator,bool> insert (const value_type& val)
		{
			if (!_root)
			{
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, map_node(val));
				_root->left = _begin;
				_root->right = _end;
				_end->parent = _root;
				_begin->parent = _root;
				_size = 1;
				return (ft::make_pair(iterator(_root), true));
			}
			iterator it = this->find(val.first);
			if (it != this->end())
				return (ft::make_pair(it, false));
			map_node *node;
			if (_compare(_end->parent->value.first, val.first))
				node = _end->parent;
			else if (!_compare(_begin->parent->value.first, val.first))
				node = _begin->parent;
			else
				node = _root;			
			while (node->right || node->left)
			{
				if (_compare(node->value.first, val.first))
				{
					if (node->right && node->right != _end)
						node = node->right;
					else
						break ;
				}
				else
				{
					if (node->left && node->left != _begin)
						node = node->left;
					else
						break ;
				}
			}
			map_node *new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, map_node(val));
			new_node->parent = node;
			if (_compare(node->value.first, val.first))
			{
				new_node->right = node->right;
				if (new_node->right)
				    new_node->right->parent = new_node;
				new_node->left = NULL;
				node->right = new_node;
			}
			else
			{
				new_node->left = node->left;
				if (new_node->left)
					new_node->left->parent = new_node;
				new_node->right = NULL;
				node->left = new_node;
			}
			_size++;
			if (_size >= 3)
				rebalance(new_node);
			return ft::make_pair(new_node, true);
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			return (insert(val).first);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			map_node *p = position.get_internal_pointer();
			map_node *tmp;
			map_node *toBalance;

			if (p == _root)
			{
				if (p->right && !p->left)
				{
					p->right->parent = NULL;
					_root = p->right;
				}
				else if (!p->right && p->left)
				{
					p->left->parent = NULL;
					_root = p->left;
				}
				else if (p->right && p->left)
				{
					if (p->right != _end)
					{
						tmp = p->findMin(p->right);
						if (tmp->parent != p)
							toBalance = tmp->parent;
						else
							toBalance = tmp;
						tmp->left = p->left;
						p->left->parent = tmp;
						if (tmp != p->right)
						{
							tmp->right = p->right;
							p->right->parent = tmp;
						}
						if (tmp->parent)
						{
							if (tmp->parent->left == tmp)
								tmp->parent->left = NULL;
							else
								tmp->parent->right = NULL;
						}
						tmp->parent = NULL;
						_root = tmp;
					}
					else if (p->left != _begin)
					{
						p->left->parent = NULL;
						tmp = p->findMax(p->left);
						if (tmp->parent != p)
							toBalance = tmp->parent;
						else
							toBalance = tmp;
						tmp->left = p->left;
						if (p->right->parent)
							p->right->parent = tmp;
						tmp->right = p->right;
						if (p->left)
							p->left->parent = tmp;
						if (tmp->parent)
						{
							if (tmp->parent->left == tmp)
								tmp->parent->left = NULL;
							else
								tmp->parent->right = NULL;
						}
						tmp->parent = NULL;
						_root = tmp;
					}
					else
					{
						_begin->parent = _end;
						_end->left = _begin;
						_root = NULL;
					}
				}
				else
				{
					_begin->parent = _end;
					_root = NULL;
				}
			}
			else if (!p->right && !p->left)
			{
				if (p->parent->right == p)
					p->parent->right = NULL;
				else
					p->parent->left = NULL;
				toBalance = p->parent;
			}
			else if (!p->right && p->left)
			{
				if (p->parent->right == p)
					p->parent->right = p->left;
				else
					p->parent->left = p->left;
				p->left->parent = p->parent;
				toBalance = p->parent;
			}
			else if (p->right && !p->left)
			{
				if (p->parent->right == p)
					p->parent->right = p->right;
				else
					p->parent->left = p->right;
				p->right->parent = p->parent;
				toBalance = p->parent;
			}
			else
			{
				if (p->left == _begin)
				{
					p->parent->left = p->right;
					p->right->parent = p->parent;
					map_node *tmp = p->findMin(p->right);
					tmp->left = p->left;
					p->left->parent = tmp;
					toBalance = p->parent;
				}
				else
				{
					map_node *max_left = p->findMax(p->left);
					if (!max_left->left && !max_left->right)
					{
						if (max_left == max_left->parent->left)
							max_left->parent->left = NULL;
						else
							max_left->parent->right = NULL;
						max_left->parent = NULL;
					}
					else if (max_left->left && !max_left->right)
					{
						if (max_left == max_left->parent->left)
							max_left->parent->left = max_left->left;
						else
							max_left->parent->right = max_left->left;
						max_left->left->parent = max_left->parent;
					}
					else if (!max_left->left && max_left->right)
					{
						if (max_left == max_left->parent->left)
							max_left->parent->left = max_left->right;
						else
							max_left->parent->right = max_left->right;
						max_left->right->parent = max_left->parent;
					}
					max_left->parent = p->parent;
					if (p->parent->left == p)
						p->parent->left = max_left;
					else
						p->parent->right = max_left;
					max_left->left = p->left;
					if (p->left)
						p->left->parent = max_left;
					max_left->right = p->right;
					if (p->right)
						p->right->parent = max_left;
					toBalance = max_left;
				}
			}
			_node_alloc.destroy(p);
			_node_alloc.deallocate(p, 1);
			_size--;
			if (_size == 0)
			{
				_root = NULL;
				_begin->right = NULL;
				_begin->left = NULL;
				_end->right = NULL;
				_end->left = NULL;
				_begin->parent = _end;
			}
			else if (_size >= 3)
				rebalance(toBalance);
		}

		size_type erase (const key_type &k)
		{
			iterator it = find(k);
			if (it == end())
				return (0);
			erase(it);
			return (1);
		}

		void erase(iterator first, iterator last)
		{
			iterator tmp;

			if (first == last)
			{
				return ;
			}
			tmp = first;
			erase(++first, last);
			erase(tmp);
		}

		void swap(map &x)
		{
			map_node	*tmp;
			size_type	size_tmp;

			if (x == *this)
				return ;

			tmp = x._root;
			x._root = _root;
			_root = tmp;

			tmp = x._end;
			x._end = _end;
			_end = tmp;

			tmp = x._begin;
			x._begin = _begin;
			_begin = tmp;

			size_tmp = x._size;
			x._size = _size;
			_size = size_tmp;
		}

		void clear(void)
		{
			this->erase(this->begin(), this->end());
		}

		//Operations

		iterator find(const key_type &k)
		{
			map_node *node;

			node = _root;
			while (node && node != _end && node != _begin && (_compare(node->value.first, k) || _compare(k, node->value.first)))
			{
				if (_compare(node->value.first, k))
					node = node->right;
				else
					node = node->left;
			}
			if (node && node != _end && node != _begin && !_compare(node->value.first, k) && !_compare(k, node->value.first))
				return iterator(node);
			else
				return iterator(_end);
		}

		const_iterator find(const key_type &k) const
		{
			map_node *node;

			node = _root;
			while (node && node != _end && node != _begin && (_compare(node->value.first, k) || _compare(k, node->value.first)))
			{
				if (_compare(node->value.first, k))
					node = node->right;
				else
					node = node->left;
			}
			if (node && node != _end && node != _begin && !_compare(node->value.first, k) && !_compare(k, node->value.first))
				return const_iterator(node);
			else
				return const_iterator(_end);
		}

		size_type count (const key_type& k) const
		{
			if (find(k) == end())
				return (0);
			return (1);
		}

		iterator lower_bound (const key_type& k)
		{
			key_compare compare = key_compare();
			for (iterator i = begin(); i != end(); i++)
			{
				if (!compare(i->first, k))
					return (i);
			}
			return (end());
		}

		const_iterator lower_bound (const key_type& k) const
		{
			key_compare compare = key_compare();
			for (const_iterator i = begin(); i != end(); i++)
			{
				if (!compare(i->first, k))
					return (i);
			}
			return (end());
		}

		iterator upper_bound (const key_type& k)
		{
			key_compare compare = key_compare();
			for (iterator i = begin(); i != end(); i++)
			{
				if (compare(k, i->first))
					return (i);
			}
			return (end());
		}

		const_iterator upper_bound (const key_type& k) const
		{
			key_compare compare = key_compare();
			for (const_iterator i = begin(); i != end(); i++)
			{
				if (compare(k, i->first))
					return (i);
			}
			return (end());
		}

		pair<iterator,iterator> equal_range (const key_type& k)
		{
			iterator first = lower_bound(k);
			iterator second = upper_bound(k);
			return (make_pair(first, second));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			const_iterator first = lower_bound(k);
			const_iterator second = upper_bound(k);
			return (make_pair(first, second));
		}

		map_node*	get_root(void)
		{
			return _root;
		}

		//Allocator

		allocator_type get_allocator(void) const
		{
			allocator_type allocator_copy(_alloc);
			return (allocator_copy);
		}

		private :

		int retHeight(map_node *node)
		{
			if (node != NULL && node != _begin && node != _end)
				return (node->height);
			return (-1);
		}

		void setHeight(map_node *node)
		{
			int left = retHeight(node->left);
			int right = retHeight(node->right);
			node->height = std::max(left, right) + 1;
		}

		int balanceFactor(map_node *node)
		{
			return (retHeight(node->right) - retHeight(node->left));
		}

		map_node *rotateRight(map_node *node)
		{
			map_node *leftChild = node->left;
			if (leftChild != NULL)
			{
				if (leftChild->right)
				{
					node->left = leftChild->right;
					leftChild->right->parent = node;
				}
				else
					node->left = NULL;
				leftChild->right = node;
				if (node->parent)
				{
					if (node->parent->left == node)
						node->parent->left = leftChild;
					else
						node->parent->right = leftChild;
				}
				else
					leftChild->parent = NULL;
				leftChild->parent = node->parent;
				node->parent = leftChild;
				if (_root == node)
					_root = leftChild;
			}
			else
				node->left = NULL;
			setHeight(node);
			setHeight(leftChild);
			return (leftChild);
		}

		map_node *rotateLeft(map_node *node)
		{
			map_node *rightChild = node->right;
			if (rightChild != NULL)
			{
				if (rightChild->left)
				{
					node->right = rightChild->left;
					rightChild->left->parent = node;
				}
				else
					node->right = NULL;
				rightChild->left = node;
				if (node->parent)
				{
					if (node->parent->left == node)
						node->parent->left = rightChild;
					else
						node->parent->right = rightChild;
				}
				else
					rightChild->parent = NULL;
				rightChild->parent = node->parent;
				node->parent = rightChild;
				if (_root == node)
					_root = rightChild;
			}
			else
				node->right = NULL;
			setHeight(node);
			setHeight(rightChild);
			return (rightChild);
		}

		void rebalance(map_node *node)
		{
			if (node == NULL)
				return ;
			while (node->parent)
			{
				setHeight(node);
				balance_a(node);
				node = node->parent;
			}
			setHeight(node);
			balance_a(node);
		}

		map_node *balance_a(map_node *node)
		{
			int bf = balanceFactor(node);
			map_node *ret;
			if (bf < -1)
			{
				if (balanceFactor(node->left) <= 0)
					ret = rotateRight(node);
				else
				{
					ret = rotateLeft(node->left);
					ret = rotateRight(node);
				}	
			}
			if (bf > 1)
			{
				if (balanceFactor(node->right) >= 0)
					ret = rotateLeft(node);
				else
				{
					ret = rotateRight(node->right);
					ret = rotateLeft(node);
				}
			}
			return (ret);
		}
	};

	//Non-member functions

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		typename ft::map<Key, T>::const_iterator rit = rhs.begin();
		typename ft::map<Key, T>::const_iterator lit = lhs.begin();
		if (lhs.size() != rhs.size())
			return false;
		while (rit != rhs.end() && lit != lhs.end())
		{
			if (*rit != *lit)
				return false;
			rit++;
			lit++;
		}
		return true;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(rhs == lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator< (const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs > rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator> (const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc> &lhs, ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return lhs.swap(rhs);
	}
}

#endif
