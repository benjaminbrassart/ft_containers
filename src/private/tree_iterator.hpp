/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/05 18:22:36 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_node.hpp"
#include "iterator.hpp"

namespace ft::avl
{
template< class Pair >
class tree_iterator : public ft::iterator< ft::bidirectional_iterator_tag, Pair >
{
	private:
	typedef Pair* pointer;
	typedef Pair const* const_pointer;
	typedef Pair& reference;
	typedef Pair const& const_reference;

	private:
	tree_node< Pair >* _node;

	public:
	tree_iterator() :
		_node(NULL),
		_nil_node()
	{
	}

	tree_iterator(tree_iterator< Pair > const& x);

	tree_iterator& operator=(tree_iterator< Pair > const& x);

	~tree_iterator();

	reference operator*()
	{
		return this->_node->pair;
	}

	const_reference operator*() const
	{
		return this->_node->pair;
	}

	pointer operator->()
	{
		return &this->_node->pair;
	}

	const_pointer operator->() const
	{
		return &this->_node->pair;
	}

	tree_iterator& operator++()
	{
		// TODO add binary tree logic
		return *this;
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp = *this;

		++*this;
		return tmp;
	}

	tree_iterator& operator--()
	{
		// TODO add binary tree logic
		return *this;
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp = *this;

		--*this;
		return tmp;
	}
};

template< class Pair1, class Pair2 >
bool operator==(tree_iterator< Pair1 > const& lhs, tree_iterator< Pair2 > const& rhs)
{
	return rhs._node == lhs._node; // TODO check value instead?
}

template< class Pair1, class Pair2 >
bool operator!=(tree_iterator< Pair1 > const& lhs, tree_iterator< Pair2 > const& rhs)
{
	return !(lhs == rhs);
}
} // namespace ft::avl
