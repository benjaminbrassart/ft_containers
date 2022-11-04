/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:42:08 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/04 21:23:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
template< class Pair, class Node >
struct tree_iterator : public ft::iterator< std::bidirectional_iterator_tag, Pair >
{
private:
	typedef Node node_type;

public:
	typedef Pair* pointer;
	typedef Pair const* const_pointer;
	typedef Pair& reference;
	typedef Pair const& const_reference;

private:
	node_type* _node;

public:
	tree_iterator() :
		_node(NULL)
	{
	}

	template< class _Node >
	explicit tree_iterator(_Node* node) :
		_node(node)
	{
	}

	template< class _Pair, class _Node >
	tree_iterator(tree_iterator< _Pair, _Node > const& x) :
		_node(x.base())
	{
	}

	template< class _Pair, class _Node >
	tree_iterator& operator=(tree_iterator< _Pair const, _Node > const& x)
	{
		if (this != &x)
			this->_node = x._node;
		return *this;
	}

	~tree_iterator()
	{
	}

public:
	node_type* base() const
	{
		return this->_node;
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
	// https://stackoverflow.com/a/9601027
	tree_iterator& operator++()
	{
		if (!this->_node->right->is_nil())
		{
			this->_node = this->_node->right;
			while (!this->_node->left->is_nil())
				this->_node = this->_node->left;
		}
		else
		{
			while (!this->_node->parent->is_nil() && this->_node == this->_node->parent->right)
				this->_node = this->_node->parent;
			this->_node = this->_node->parent;
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
		if (!this->_node->left->is_nil())
		{
			this->_node = this->_node->left;
			while (!this->_node->right->is_nil())
				this->_node = this->_node->right;
		}
		else
		{
			while (!this->_node->parent->is_nil() && this->_node == this->_node->parent->left)
				this->_node = this->_node->parent;
			this->_node = this->_node->parent;
		}
		return *this;
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp = *this;

		--*this;
		return tmp;
	}
};

template< class Pair1, class Node1, class Pair2, class Node2 >
bool operator==(tree_iterator< Pair1, Node1 > const& lhs, tree_iterator< Pair2, Node2 > const& rhs)
{
	return rhs.base() == lhs.base();
}

template< class Pair1, class Node1, class Pair2, class Node2 >
bool operator!=(tree_iterator< Pair1, Node1 > const& lhs, tree_iterator< Pair2, Node2 > const& rhs)
{
	return !(lhs == rhs);
}
} // namespace ft

#endif // TREE_ITERATOR_HPP
