#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../iterators/utils.hpp"
#include "../iterators/iterator_traits.hpp"
#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> > class vector
	{
		public:

			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef VectorIterator<pointer>					    	iterator;
			typedef VectorIterator<const_pointer>			    	const_iterator;
			typedef ft::reverse_iterator<iterator>				    reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		    const_reverse_iterator;

			private:
				size_type _size;
				size_type _capacity;
				pointer _i;
				allocator_type _alloc;

				void destroy_and_deallocate(void)
				{
					for (size_t i = 0; i < this->_size; i++)
					{
						this->_alloc.destroy(this->_i + i);
					}
					this->_alloc.deallocate(this->_i, this->_capacity);
				}

				void realloc(size_type n)
				{
					value_type *new_i = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&new_i[i], _i[i]);
					destroy_and_deallocate();
					_i = new_i;
					_capacity = n;
				}

			public:

				explicit vector(const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _i(NULL), _alloc(alloc)
				{
						
				}

				vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(0), _capacity(n), _alloc(alloc)
				{
					_i = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _capacity; i++, _size++)
						_alloc.construct(_i + _size, val);
				}

				template <class InputIterator>
				vector(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type()): _size(0), _capacity(ft::distance(first, last)), _alloc(alloc)
				{
					_i = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _capacity; i++, _size++)
						_alloc.construct(_i + _size, *(first++));
				}

				explicit vector(const ft::vector<value_type> & copy): _size(0), _capacity(copy._capacity), _alloc(copy._alloc) {
					this->_i = this->_alloc.allocate(this->_capacity);
					for (size_type i = 0; i < copy._size; i++, _size++)
					{
						this->_alloc.construct(this->_i + _size, *(copy._i + _size));
					}	
				}

				virtual ~vector()
				{
					for (size_type i = 0; i < this->_size; i++)
					{
						this->_alloc.destroy(this->_i + i);
					}
					_alloc.deallocate(_i, _size);
				}

				vector &operator=(vector const &copy)
				{
					this->clear();
					if (this->_capacity < copy.size())
						this->reserve(copy.size());
					for (size_type i = 0; i < copy.size(); i++)
					{
						this->_alloc.construct(this->_i + i, *(copy._i + i));
					}
					this->_size = copy.size();
					return (*this);
				}

				//Iterators
				iterator begin(void)
				{
					return (this->_i);
				}

				const_iterator begin(void) const
				{
					return (this->_i);
				}

				iterator end()
				{
					return (iterator(this->_i + (this->_size)));
				}

				const_iterator end() const
				{
					return (const_iterator(this->_i + (this->_size)));
				}

				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->_i + (this->_size)));
				}
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->_i + (this->_size)));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(this->begin()));
				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(this->begin()));
				}

				//Capacity

				size_type size() const
				{
					return (this->_size);
				}

				size_type max_size() const
				{
					return (std::numeric_limits<size_type>::max() / sizeof(value_type));
				}

				void resize(size_type n, const value_type& val = value_type())
				{
					if (n < _size)
					{
						for (size_type i = n; i < _size; ++i)
							_alloc.destroy(_i + i);
					}
					else if (n > size())
					{
						if (n > capacity())
						{
							if (capacity() * 2 < n)
								reserve(n);
							else
								reserve(capacity() * 2);
						}
						for (size_type i = _size; i < n; ++i)
							_alloc.construct(_i + i, val);
					}
					_size = n;  
				}

				size_type capacity() const
				{
					return (this->_capacity);
				}

				bool empty() const
				{
					if (_size == 0)
						return (true);
					return (false);
				}

				void reserve(size_type n)
				{
					if (n > max_size())
						throw std::length_error::exception();
					if (n > this->_capacity)
						realloc(n);
				}

				void shrink_to_fit(void)
				{
					realloc(this->_size);
				}

				//Element access

				reference operator[] (size_type n)
				{
					return (*(this->_i + n));
				}

				const_reference operator[] (size_type n) const
				{
					return (*(this->_i + n));
				}

				reference at(size_type n)
				{
					if (n > this->_size)
						throw std::out_of_range("vector");
					return (*(this->_i + n));
				}

				const_reference at(size_type n) const
				{
					if (n > this->_size)
						throw std::out_of_range("vector");
					return (*(this->_i + n));
				}

				reference front()
				{
					return (*this->_i);
				}

				const_reference front() const
				{
					return (*this->_i);
				}

				reference back()
				{
					return (*(this->_i + (this->_size - 1)));
				}

				const_reference back() const
				{
					return (*(this->_i + (this->_size - 1)));
				}

				//Modifiers

				template <class InputIterator>
				void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type* = 0)
				{
					size_type length = ft::distance(first, last);
					if (this->_size > this->_capacity)
						throw std::length_error::exception();
					if (length > this->_capacity)
						this->reserve(length);
					this->clear();
					for (size_type i = 0; i < length; i++, first++)
					{
						this->_alloc.construct(this->_i + i, *first);
					}
					this->_size = length;
				}

				void assign(size_type n, const T& val)
				{
					if (n > capacity())
					{
						pointer tmp = _alloc.allocate(n);
						for (size_type i = 0; i < n; i++)
						{
							_alloc.construct(tmp + i, val);
							if (capacity())
								_alloc.destroy(_i + i);
						}
						if (capacity())
							_alloc.deallocate(_i, _capacity);
						_i = tmp;
						_capacity = n;
						_size = n;
					}
					else
					{
						for (size_type i = 0; i < n; i++)
						{
							_alloc.construct(_i + i, val);
							_alloc.destroy(_i + i);
						}
						_size = n;
					}
				}

				void push_back(const value_type& val)
				{
					if (this->_size >= this->_capacity)
					{
						if (_capacity == 0)
							realloc(1);
						else
							realloc(_capacity * 2);
					}
					_alloc.construct(&_i[_size], val);
					this->_size++;
				}

				void pop_back(void)
				{
					this->_alloc.destroy(this->_i + this->_size);
					this->_size--;
				}

				iterator insert(iterator position, const value_type& val)
				{
					size_type pos = position - this->begin();
					if (this->_size == this->_capacity)
						realloc(this->_capacity * 2);
					for (size_type i = this->_size; i > pos; i--)
					{
						this->_alloc.construct(this->_i + i, *(this->_i + i - 1));
					}
					this->_alloc.construct(this->_i + pos, val);
					this->_size += 1;
					return (this->begin() + pos);
				}

				void insert(iterator position, size_type n, const value_type& val)
				{
					size_type pos = position - this->begin();
					if (this->_size + n > this->_capacity)
					{
						if (n > this->_size)
						{
							if (n <= (this->_capacity * 2))
								realloc(this->_capacity * 2);
							else
								realloc(this->_size + n);
						}
					}
					position = iterator(this->_i + pos);
					for (size_type i = 0; i < n; i++)
						position = this->insert(position, val);
				}

				template <typename InputIt>
				void insert(iterator position, InputIt first, InputIt last, typename enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt()){
					size_type index = position - begin();
					if (index <= _capacity)
					{
						value_type *tmp = _i;
						size_type	size_tmp = _size;
						size_type	capacity_tmp = _capacity;
						_i = _alloc.allocate(_capacity);

						for (size_type i = 0; i < index; i++)
						{
							_alloc.construct(&_i[i], tmp[i]);
							_alloc.destroy(&tmp[i]);
						}

						_size = index;

						for ( ; first != last; first++)
							push_back(*first);

						for (size_type i = index; i < size_tmp; i++)
						{
							push_back(tmp[i]);
							_alloc.destroy(&tmp[i]);
						}
						_alloc.deallocate(tmp, capacity_tmp);
					}
				}

				iterator erase(iterator position)
				{
					size_type index = ft::distance(begin(), position);
					for (size_type i = index; i != _size; ++i)
					{
						_alloc.destroy(_i + i);
						if (i + 1 != _size)
							_alloc.construct(_i + i, *(_i + i + 1));
					}
					_size--;
					return begin() + index;
				}

				iterator erase(iterator first, iterator last)
				{
					size_type index_first = ft::distance(begin(), first);
					size_type index_last = ft::distance(begin(), last);
					size_type n = index_last - index_first;
					for (size_type i = index_first; i < index_last; ++i)
						_alloc.destroy(_i + i);
					for (size_type i = index_last; i < _size; ++i)
						_alloc.construct(_i + (i - n), *(_i + i));
					_size -= n;
					return first;
				}

				void swap(vector& x)
				{
					value_type *tab_temp = x._i;
					size_type size_temp = x._size;
					size_type capacity_temp = x._capacity;
					allocator_type alloc_temp = x._alloc;

					x._i = this->_i;
					x._size = this->_size;
					x._capacity = this->_capacity;
					x._alloc = this->_alloc;

					this->_i = tab_temp;
					this->_size = size_temp;
					this->_capacity = capacity_temp;
					this->_alloc = alloc_temp;
				}

				value_type* data()
				{
					return (this->_i);
				}

				const value_type* data() const
				{
					return (this->_i);
				}

				void clear()
				{
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_i + i);
					this->_size = 0;                
				}

				allocator_type get_allocator(void) const
				{
					allocator_type allocator_copy(this->_alloc);
					return (allocator_copy);
				}
	};

	template <class T, class Alloc>
	void swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

}

#endif
