/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:46:23 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/03 08:13:15 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

// TODO fix and test with Mazoise
namespace ft
{
template< class T, class Container = ft::vector< T > >
class stack
{
public:
	typedef Container container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::size_type size_type;

public:
	container_type c;

public:
	stack(container_type const& container = container_type()) :
		c(container)
	{
	}

	stack(stack const& x) :
		c(x.c)
	{
	}

	stack& operator=(stack const& rhs)
	{
		if (this != &rhs)
			this->c = rhs.c;
		return *this;
	}

	~stack()
	{
	}

public:
	value_type& top()
	{
		return this->c.back();
	}

	value_type const& top() const
	{
		return this->c.back();
	}

	bool empty() const
	{
		return this->c.empty();
	}

	size_type size() const
	{
		return this->c.size();
	}

	void push(value_type const& value)
	{
		this->c.push_back(value);
	}

	void pop()
	{
		this->c.pop_back();
	}

	template< class _T, class _Container >
	friend bool operator==(stack< _T, _Container > const& lhs, stack< _T, _Container > const& rhs);

	template< class _T, class _Container >
	friend bool operator!=(stack< _T, _Container > const& lhs, stack< _T, _Container > const& rhs);

	template< class _T, class _Container >
	friend bool operator<(stack< _T, _Container > const& lhs, stack< _T, _Container > const& rhs);

	template< class _T, class _Container >
	friend bool operator<=(stack< _T, _Container > const& lhs, stack< _T, _Container > const& rhs);

	template< class _T, class _Container >
	friend bool operator>(stack< _T, _Container > const& lhs, stack< _T, _Container > const& rhs);

	template< class _T, class _Container >
	friend bool operator>=(stack< _T, _Container > const& lhs, stack< _T, _Container > const& rhs);
};

template< class T, class Container >
bool operator==(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
{
	return lhs.c == rhs.c;
}

template< class T, class Container >
bool operator!=(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
{
	return lhs.c != rhs.c;
}

template< class T, class Container >
bool operator<(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
{
	return lhs.c < rhs.c;
}

template< class T, class Container >
bool operator<=(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
{
	return lhs.c <= rhs.c;
}

template< class T, class Container >
bool operator>(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
{
	return lhs.c > rhs.c;
}

template< class T, class Container >
bool operator>=(stack< T, Container > const& lhs, stack< T, Container > const& rhs)
{
	return lhs.c >= rhs.c;
}
} // namespace ft
