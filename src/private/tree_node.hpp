/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:23:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/05 22:00:01 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
namespace avl {
template< class Pair, class Compare, class Alloc >
struct tree;

template< class Pair, class Compare, class Alloc >
struct tree_node
{
	ft::avl::tree< Pair, Compare, Alloc >* tree;
	ft::avl::tree_node< Pair, Compare, Alloc >* parent;
	Pair pair;
	ft::avl::tree_node< Pair, Compare, Alloc >* left;
	ft::avl::tree_node< Pair, Compare, Alloc >* right;
	int height;

	private:
	tree_node() :
		parent(NULL),
		pair(),
		left(NULL),
		right(NULL),
		height(0)
	{
	}

	public:
	tree_node(ft::avl::tree_node< Pair, Compare, Alloc >* p_parent, Pair const& p_pair) :
		parent(p_parent),
		pair(p_pair),
		left(NULL),
		right(NULL),
		height(1)
	{
	}

	tree_node(ft::avl::tree_node< Pair, Compare, Alloc > const& x) :
		parent(x.parent),
		pair(x.pair),
		left(x.left),
		right(x.right),
		height(x.height)
	{
	}

	tree_node& operator=(ft::avl::tree_node< Pair, Compare, Alloc > const& x)
	{
		if (&x != this)
		{
			this->parent = x.parent;
			this->pair = x.pair;
			this->left = x.left;
			this->right = x.right;
			this->height = x.height;
		}
		return *this;
	}

	~tree_node()
	{
	}

	public:
	bool is_nil() const
	{
		return this->parent == NULL;
	}
};
} // namespace avl
} // namespace ft
