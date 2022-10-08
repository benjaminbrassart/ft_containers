/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/07 22:28:15 by bbrassar         ###   ########.fr       */
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
class tree_iterator : public ft::iterator< ft::bidirectional_iterator_tag, Pair >
{
	private:
	typedef Pair* pointer;
	typedef Pair const* const_pointer;
	typedef Pair& reference;
	typedef Pair const& const_reference;
	typedef tree_node< Pair > node_type;

	public:
	node_type* _node;

	public:
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

	pointer operator->()
	{
		return &this->_node->pair;
	}

	tree_iterator& operator++()
	{
		// TODO add binary tree logic

		if (this->_node->right->is_nil())
		{
			if (this->_node->parent->left == this)
			{
				this->_node = this->_node->parent;
			}
			else
			{

			}
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
