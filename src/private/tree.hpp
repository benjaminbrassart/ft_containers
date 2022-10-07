/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:24:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/05 22:00:09 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_node.hpp"
#include "utils.hpp"

namespace ft
{
namespace avl {
template<
	class Pair,
	class Compare,
	class Alloc
>
struct tree
{
	private:
	typedef ft::avl::tree_node< Pair > Node;
	typedef Pair value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type;

	private:
	Alloc _alloc;
	Node _nil_node;
	Node* _root;
	Node* _min;
	Node* _max;
	size_type _size;

	public:
	tree(allocator_type const& alloc) :
		_alloc(alloc),
		_nil_node(),
		_root(NULL),
		_min(NULL),
		_max(NULL),
		_size(0)
	{
	}

	tree(ft::avl::tree< Pair, Compare, Alloc > const& x) :
		_alloc(x._alloc),
		_nil_node(),
		_root(NULL),
		_min(NULL),
		_max(NULL),
		_size(0)
	{
	}

	tree& operator=(ft::avl::tree< Pair, Compare, Alloc > const& x)
	{
		if (this != &x)
		{
			this->_alloc = x._alloc;
			this->__udpdate_nil();
		}
		return *this;
	}

	~tree()
	{
		this->__delete_all(this->_root);
	}

	private:
	void __udpdate_nil()
	{
		this->_nil_node.left = this->_min;
		this->_nil_node.right = this->_max;
	}

	void __delete_all(Node* node)
	{
		if (node->parent == NULL)
			return;
		__delete(node->right);
		__delete(node->left);
		this->_alloc.destroy(node);
		this->_alloc.dealloc(node, 1);
	}
};
} // namespace avl
} // namespace ft
