/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/14 11:27:24 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_node.hpp"
#include "iterator.hpp"

namespace ft
{
namespace avl
{
template< class Pair >
struct tree_iterator : public ft::iterator< ft::bidirectional_iterator_tag, Pair >
{
	typedef Pair* pointer;
	typedef Pair const* const_pointer;
	typedef Pair& reference;
	typedef Pair const& const_reference;
	typedef tree_node< Pair > node_type;

	node_type* _node;

	tree_iterator() :
		_node(NULL)
	{
	}

	tree_iterator(node_type* node) :
		_node(node)
	{
	}

	tree_iterator(tree_iterator< Pair > const& x) :
		_node(x._node)
	{
	}

	tree_iterator& operator=(tree_iterator< Pair > const& x)
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

	// TODO test this
	// https://stackoverflow.com/questions/12684191/implementing-an-iterator-over-binary-or-arbitrary-tree-using-c-11/12684730#12684730
	tree_iterator& operator++()
	{
		node_type* y;

		if (!this->_node->right->is_nil())
		{
			this->_node = this->_node->right;
			while (!this->_node->left->is_nil())
				this->_node = this->_node->left;
		}
		else
		{
			y = this->_node->parent;
			while (this->_node == y->right)
			{
				this->_node = y;
				y = y->parent;
			}
			if (this->_node->right != y)
				this->_node = y;
		}
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

template< class Pair >
bool operator==(tree_iterator< Pair > const& lhs, tree_iterator< Pair > const& rhs)
{
	return rhs._node == lhs._node; // TODO check value instead?
}

template< class Pair >
bool operator!=(tree_iterator< Pair > const& lhs, tree_iterator< Pair > const& rhs)
{
	return !(lhs == rhs);
}
} // namespace avl
} // namespace ft
