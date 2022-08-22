/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:46:23 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/22 21:03:34 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector< T > >
	class stack
	{
		public:
		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef typename container_type::size_type size_type;

		protected:
		container_type c;

		public:
		// TODO test implementation
		stack(container_type const& container = container_type()) :
			c(container)
		{
		}

		// TODO test implementation
		stack(stack const& x) :
			c(x.c)
		{
		}

		// TODO test implementation
		stack& operator=(stack const& rhs)
		{
			if (this != &rhs)
			{
				this->c = rhs.c;
			}
			return *this;
		}

		// TODO test implementation
		~stack()
		{
		}

		public:
		// TODO test implementation
		value_type& top()
		{
			return this->c.back();
		}

		// TODO test implementation
		value_type const& top() const
		{
			return this->c.back();
		}

		// TODO test implementation
		bool empty() const
		{
			return this->c.empty();
		}

		// TODO test implementation
		size_type size() const
		{
			return this->c.size();
		}

		// TODO test implementation
		void push(value_type const& value)
		{
			this->c.push_back(value);
		}

		// TODO test implementation
		void pop()
		{
			this->c.pop_back();
		}

		template< class T, class Container >
		friend bool operator==(stack< T, Container > const& lhs, stack< T, Container > const& rhs);

		template< class T, class Container >
		friend bool operator!=(stack< T, Container > const& lhs, stack< T, Container > const& rhs);

		template< class T, class Container >
		friend bool operator<(stack< T, Container > const& lhs, stack< T, Container > const& rhs);

		template< class T, class Container >
		friend bool operator<=(stack< T, Container > const& lhs, stack< T, Container > const& rhs);

		template< class T, class Container >
		friend bool operator>(stack< T, Container > const& lhs, stack< T, Container > const& rhs);

		template< class T, class Container >
		friend bool operator>=(stack< T, Container > const& lhs, stack< T, Container > const& rhs);
	};

	// TODO test implementation
	template< class T, class Container >
	bool operator==(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
	{
		return lhs.c == rhs.c;
	}

	// TODO test implementation
	template< class T, class Container >
	bool operator!=(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
	{
		return lhs.c != rhs.c;
	}

	// TODO test implementation
	template< class T, class Container >
	bool operator<(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
	{
		return lhs.c < rhs.c;
	}

	// TODO test implementation
	template< class T, class Container >
	bool operator<=(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
	{
		return lhs.c <= rhs.c;
	}

	// TODO test implementation
	template< class T, class Container >
	bool operator>(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
	{
		return lhs.c > rhs.c;
	}

	// TODO test implementation
	template< class T, class Container >
	bool operator>=(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
	{
		return lhs.c >= rhs.c;
	}
} // namespace ft
