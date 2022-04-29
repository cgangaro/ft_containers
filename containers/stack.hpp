#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template< typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:

			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;
		
		protected:

			container_type _container;
		
		public:

			stack(const container_type& ctnr = container_type()): _container(ctnr)
			{
			}

			bool empty() const
			{
				return (_container.empty());
			}

			size_type size() const
			{
				return (_container.size());
			}

			value_type& top()
			{
				return (_container.back());
			}

			const value_type& top() const
			{
				return (_container.back());
			}

			void push (const value_type& val)
			{
				_container.push_back(val);
			}

			void pop()
			{
				_container.pop_back();
			}

			template <class stack_t, class cont_t>
			friend bool operator== (const stack<stack_t,cont_t>& lhs, const stack<stack_t,cont_t>& rhs)
			{
				return (lhs._container == rhs._container);
			}

			template <class stack_t, class cont_t>
			friend bool operator!= (const stack<stack_t,cont_t>& lhs, const stack<stack_t,cont_t>& rhs)
			{
				return !(lhs._container == rhs._container);
			}

			template <class stack_t, class cont_t>
			friend bool operator< (const stack<stack_t,cont_t>& lhs, const stack<stack_t,cont_t>& rhs)
			{
				return (lhs._container < rhs._container);
			}

			template <class stack_t, class cont_t>
			friend bool operator<= (const stack<stack_t,cont_t>& lhs, const stack<stack_t,cont_t>& rhs)
			{
				return (lhs._container <= rhs._container);
			}

			template <class stack_t, class cont_t>
			friend bool operator>  (const stack<stack_t,cont_t>& lhs, const stack<stack_t,cont_t>& rhs)
			{
				return (lhs._container > rhs._container);
			}

			template <class stack_t, class cont_t>
			friend bool operator>= (const stack<stack_t,cont_t>& lhs, const stack<stack_t,cont_t>& rhs)
			{
				return (lhs._container >= rhs._container);
			}
	};
	
}

#endif
