/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:23:25 by bbrassar          #+#    #+#             */
/*   Updated: 2022/09/23 19:46:50 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NULL ((void*)0)

namespace ft::avl
{
template< class Pair >
struct tree_node
{
	tree_node* parent;
	Pair pair;
	tree_node* left;
	tree_node* right;
	int height;

	private:
	tree_node();

	public:
	tree_node(tree_node* p_parent, Pair const& p_pair) :
		parent(p_parent),
		pair(p_pair),
		left(NULL),
		right(NULL),
		height(1)
	{
	}

	tree_node(tree_node const& x) :
		parent(x.parent),
		pair(x.pair),
		left(x.left),
		right(x.right),
		height(x.height)
	{
	}

	tree_node& operator=(tree_node const& x)
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
