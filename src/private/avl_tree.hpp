/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/18 15:18:16 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_iterator.hpp"
#include "private/tree_node.hpp"

namespace ft
{
namespace avl
{

template< class Value, class Compare, class Alloc >
class tree
{
	/* ------------------------------------------------------------------------- */
private:
	typedef Value value_type;
	typedef typename value_type::first_type key_type;
	typedef Compare value_compare;
	typedef ft::avl::tree_node< value_type > node_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type;
	typedef ft::avl::tree_iterator< value_type, node_type > iterator;

	/* ------------------------------------------------------------------------- */

private:
	allocator_type _alloc;
	node_type* _nil;
	node_type* _root;
	node_type* _min;
	node_type* _max;
	value_compare _comp;
	size_type _size;

	/* ------------------------------------------------------------------------- */

public:
	tree(value_compare const& comp, allocator_type const& alloc) :
		_alloc(alloc),
		_nil(),
		_root(),
		_min(),
		_max(),
		_comp(comp),
		_size(0)
	{
	}

	// ? deep copy
	template< class _Value, class _Compare, class _Alloc >
	tree(tree< _Value, _Compare, _Alloc > const& x) :
		_alloc(x._alloc),
		_nil(x._nil),
		_root(x._root),
		_min(x._min),
		_max(x._max),
		_comp(x._comp),
		_size(x._size)
	{
	}

	// ? deep copy
	template< class _Value, class _Compare, class _Alloc >
	tree& operator=(tree< _Value, _Compare, _Alloc > const& x)
	{
		if (&this != &x)
		{
			this->_alloc = x._alloc;
			this->_nil = x._nil;
			this->_root = x._root;
			this->_min = x._min;
			this->_max = x._max;
			this->_comp = x._comp;
			this->_size = x._size;
		}
		return *this;
	}

	~tree()
	{
		this->clear();
		this->__delete_node(this->_nil);
	}

	/* ------------------------------------------------------------------------- */

public:
	node_type* nil()
	{
		return this->_nil;
	}

	node_type* root()
	{
		return this->_root;
	}

	node_type* min()
	{
		return this->_min;
	}

	node_type* max()
	{
		return this->_max;
	}

	value_compare const& comp()
	{
		return this->_comp;
	}

	size_type size()
	{
		return this->_size;
	}

	/* ------------------------------------------------------------------------- */

public:
	ft::pair< iterator, bool > insert(value_type const& val)
	{
		node_type* node;
		bool inserted;

		node = this->__insert(val, inserted);
		return ft::make_pair(iterator(node), inserted);
	}

	void clear()
	{
		this->__release(this->_root);
	}

	/* ------------------------------------------------------------------------- */

public:
	allocator_type get_allocator()
	{
		return this->_alloc;
	}

	/* ------------------------------------------------------------------------- */

private:
	node_type* __make_nil()
	{
		node_type* node = this->get_allocator().allocate(1);
		node_type tmp;

		tmp.left = this->_nil;
		tmp.right = this->_nil;

		this->get_allocator().construct(node, tmp);
		return node;
	}

	node_type* __make_node(value_type const& value)
	{
		node_type* node = this->get_allocator().allocate(1);
		node_type tmp(this->_nil, value);

		tmp.left = this->_nil;
		tmp.right = this->_nil;

		this->get_allocator().construct(node, tmp);
		return node;
	}

	void __delete_node(node_type* node)
	{
		this->get_allocator().destroy(node);
		this->get_allocator().deallocate(node, 1);
	}

	node_type* __search(key_type const& key, node_type* node)
	{
		if (node->is_nul())
			return node;
		if (this->comp()(value, node->pair))
			return this->__search(key, node->left);
		if (this->comp()(node->pair, value))
			return this->__search(key, node->right);
		return node;
	}

	node_type* __insert(value_type const& value, node_type* node, bool& inserted)
	{
		if (node->is_nil())
		{
			inserted = true;
			return this->__make_node(value);
		}
		if (this->comp()(value, node->pair))
			node->left = this->__insert(value, node->left, inserted);
		else if (this->comp()(node->pair, value))
			node->right = this->__insert(value, node->right, inserted);
		else
		{
			inserted = false;
			return node;
		}
		this->__update_height(node);
		return this->__rebalance(node);
	}

	node_type* __remove(value_type const& value, node_type* node)
	{
		if (node->is_nil())
			return node;
		if (this->comp()(value, node->pair))
			node->left = this->__remove(value, node->left);
		else if (this->comp()(node->pair, value))
			node->right = this->__remove(value, node->right);
		else
		{
			// has 0 or 1 child
			if (node->left->is_nil())
				return node->right;
			else if (this->right->is_nil())
				return node->left;

			// has 2 children
			node->pair = this->max()->pair; // swap pointers instead
			node->left = this->__remove(node->pair, node->left);
		}
		this->__update_height(node);
		return this->__rebalance(node);
	}

	void __update_height(node_type* node)
	{
		int height_max;

		height_max = node->left->height;
		if (node->right->height > height_max)
			height_max = node->right->height;
		node->height = max_height + 1;
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
			return this->__rotate_left(node);
		}
		return node;
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

	void __release(node_type* node)
	{
		if (node->is_nil())
			return;
		this->__release(node->left);
		this->__release(node->right);
		this->__delete_node(node);
	}

	bool __is_balanced(node_type* node)
	{
		return this->__abs(node->left->height - node->right->height) <= 1;
	}

	bool __check_balance(node_type* node)
	{
		return this->__is_balanced(node) && this->__is_balanced(node->left) && this->__is_balanced(node->right);
	}

	static int __abs(int a)
	{
		return (a < 0) ? -a : a;
	}
};

} // namespace avl
} // namespace ft
