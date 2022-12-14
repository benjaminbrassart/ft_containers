/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:23:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/04 22:11:35 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

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

	tree_node(ft::avl::tree_node< Pair > const& x) :
		parent(x.parent),
		pair(x.pair),
		left(x.left),
		right(x.right),
		height(x.height)
	{
	}

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
		return this->left->height - this->right->height;
	}

	void swap(tree_node& x)
	{
		std::swap(this->parent, x.parent);
		std::swap(this->pair, x.pair);
		std::swap(this->left, x.left);
		std::swap(this->right, x.right);
		std::swap(this->height, x.height);
	}
};

template< class P1, class P2 >
bool operator==(ft::avl::tree_node< P1 > const& lhs, ft::avl::tree_node< P2 > const& rhs)
{
	return &lhs == &rhs;
}

template< class P1, class P2 >
bool operator!=(ft::avl::tree_node< P1 > const& lhs, ft::avl::tree_node< P2 > const& rhs)
{
	return !(lhs == rhs);
}

} // namespace avl
} // namespace ft

#endif // TREE_NODE_HPP
