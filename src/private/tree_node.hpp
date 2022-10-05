/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:23:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/05 17:53:13 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NULL ((void*)0)

namespace ft::avl
{

class tree;

template< class Pair >
struct tree_node
{
	ft::avl::tree* tree;
	ft::avl::tree_node< Pair >* parent;
	Pair pair;
	ft::avl::tree_node< Pair >* left;
	ft::avl::tree_node< Pair >* right;
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
	tree_node(ft::avl::tree_node* p_parent, Pair const& p_pair) :
		parent(p_parent),
		pair(p_pair),
		left(NULL),
		right(NULL),
		height(1)
	{
	}

	tree_node(ft::avl::tree_node const& x) :
		parent(x.parent),
		pair(x.pair),
		left(x.left),
		right(x.right),
		height(x.height)
	{
	}

	tree_node& operator=(ft::avl::tree_node const& x)
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
};
} // namespace ft::avl
