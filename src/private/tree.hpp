/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:24:48 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/07 21:14:54 by bbrassar         ###   ########.fr       */
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
	typedef ft::avl::tree_node< Pair > node_type;
	typedef Pair value_type;
	typedef Compare comp_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type;

	public:
	Alloc _alloc;
	node_type _nil_node;
	node_type* _root;
	node_type* _min;
	node_type* _max;
	size_type _size;
	comp_type _comp;

	public:
	tree(allocator_type const& alloc, comp_type const& comp) :
		_alloc(alloc),
		_nil_node(),
		_root(NULL),
		_min(NULL),
		_max(NULL),
		_size(0),
		_comp(comp)
	{
	}

	tree(ft::avl::tree< Pair, Compare, Alloc > const& x) :
		_alloc(x._alloc),
		_nil_node(),
		_root(NULL),
		_min(NULL),
		_max(NULL),
		_size(0),
		_comp(x._comp)
	{
	}

	tree& operator=(ft::avl::tree< Pair, Compare, Alloc > const& x)
	{
		if (this != &x)
		{
			this->_alloc = x._alloc;
			this->_comp = x._comp;
			this->__udpdate_nil();
		}
		return *this;
	}

	~tree()
	{
		this->__delete_all(this->_root);
	}

	public:
	void insert(value_type const& value)
	{
		node_type* node = this->__make_node(value);
	}

	private:
	void __udpdate_nil()
	{
		this->_nil_node.left = this->_min;
		this->_nil_node.right = this->_max;
	}

	void __delete_all(node_type* node)
	{
		if (node->parent == NULL)
			return;
		__delete(node->right);
		__delete(node->left);
		this->_alloc.destroy(node);
		this->_alloc.dealloc(node, 1);
	}

	node_type* __make_node(value_type const& value)
	{
		node_type tmp(this->_nil_node, value);

		tmp.right = this->_nil_node;
		tmp.left = this->_nil_node;

		node_type* new_node = this->_alloc.allocate(1);

		this->_alloc.construct(new_node, tmp);

		return new_node;
	}

	node_type* __rotate_right(node_type* node)
	{
		node_type* left = node->left;
		node_type* center = left->right;

		left->right = node;
		node->left = center;
		this->__update_height(node);
		this->__update_height(left);
		return left;
	}

	node_type* __rotate_left(node_type* node)
	{
		node_type* right = node->right;
		node_type* center = right->left;

		right->left = node;
		node->right = center;
		this->__update_height(node);
		this->__update_height(right);
		return right;
	}

	void __update_height(node_type* node)
	{
		node->height = std::max(
			node->left->height,
			node->right->height
		) + 1;
	}

	node_type* __rebalance(node_type* node)
	{
		int balance = node->get_balance();
		int balance_next;

		if (balance > 1)
		{
			balance_next = node->left->get_balance();
			if (balance_next < 0)
				node->left = this->__rotate_left(node->left);
			return this->__rotate_right(node);
		}
		else if (balance < -1)
		{
			balance_next = node->right->get_balance();
			if (balance_next > 0)
				node->right = this->__rotate_right(node->right);
			return __rotate_left(node);
		}
		return node;
	}

	void __release(node_type* node)
	{
		if (node->is_nil())
			return ;
		this->__release(node->left);
		this->__release(node->right);
		this->_alloc.destroy(node);
		this->_alloc.deallocate(node, 1);
	}

	bool __is_balanced(node_type* node)
	{
		int const balance = node->get_balance();

		return balance >= -1 && balance <= 1;
	}

	bool __check_balance(node_type* node)
	{
		return (this->__is_balanced(node))
			&& (this->__check_balance(node->left))
			&& (this->__check_balance(node->right));
	}
};
} // namespace avl
} // namespace ft
