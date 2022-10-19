/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:23:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/19 10:48:19 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
namespace avl
{
template< class Pair >
struct tree_node
{
	/* --------------------------------------------------------------------- */

	ft::avl::tree_node< Pair >* parent;
	Pair pair;
	ft::avl::tree_node< Pair >* left;
	ft::avl::tree_node< Pair >* right;
	int height;

	/* --------------------------------------------------------------------- */

public:
	tree_node() :
		parent(0),
		pair(),
		left(0),
		right(0),
		height(0)
	{
	}

	/* --------------------------------------------------------------------- */

public:
	tree_node(ft::avl::tree_node< Pair >* p_parent, Pair const& p_pair) :
		parent(p_parent),
		pair(p_pair),
		left(0),
		right(0),
		height(1)
	{
	}

	// TODO deep copy
	tree_node(ft::avl::tree_node< Pair > const& x) :
		parent(x.parent),
		pair(x.pair),
		left(x.left),
		right(x.right),
		height(x.height)
	{
	}

	// TODO deep copy
	tree_node& operator=(ft::avl::tree_node< Pair > const& x)
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

	/* --------------------------------------------------------------------- */

public:
	bool is_nil() const
	{
		return this->parent == 0;
	}

	int get_balance() const
	{
		if (this->is_nil())
			return 0;
		return this->left.height - this->right.height;
	}
};
} // namespace avl
} // namespace ft
