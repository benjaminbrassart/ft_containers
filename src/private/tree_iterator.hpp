/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/17 10:30:52 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_node.hpp"
#include "iterator.hpp"

namespace ft
{
namespace avl
{
template< class Pair, class Node >
struct tree_iterator : public ft::iterator< ft::bidirectional_iterator_tag, Pair >
{
	public:
	typedef Pair* pointer;
	typedef Pair const* const_pointer;
	typedef Pair& reference;
	typedef Pair const& const_reference;
	typedef Node node_type;

	node_type* _node;

	tree_iterator() :
		_node(NULL)
	{
	}

	template< class _Node >
	tree_iterator(_Node* node) :
		_node(node)
	{
	}

	template< class _Pair, class _Node >
	tree_iterator(tree_iterator< _Pair, _Node > const& x) :
		_node(x._node)
	{
	}

	template< class _Pair, class _Node >
	tree_iterator& operator=(tree_iterator< _Pair, _Node > const& x)
	{
		if (this != &x)
			this->_node = x._node;
		return *this;
	}

	~tree_iterator()
	{
	}

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

	// https://stackoverflow.com/a/12684730
	tree_iterator& operator++()
	{
		TODO();
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp = *this;

		++*this;
		return tmp;
	}

	// same as above but reversed
	tree_iterator& operator--()
	{
		TODO();
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp = *this;

		--*this;
		return tmp;
	}
};

template<
	class Pair1, class Node1,
	class Pair2, class Node2
>
bool operator==(tree_iterator< Pair1, Node1 > const& lhs, tree_iterator< Pair2, Node2 > const& rhs)
{
	return rhs._node == lhs._node; // TODO check value instead?
}

template<
	class Pair1, class Node1,
	class Pair2, class Node2
>
bool operator!=(tree_iterator< Pair1, Node1 > const& lhs, tree_iterator< Pair2, Node2 > const& rhs)
{
	return !(lhs == rhs);
}
} // namespace avl
} // namespace ft
