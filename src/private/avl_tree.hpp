/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/27 03:35:08 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_iterator.hpp"
#include "private/tree_node.hpp"

#include <algorithm>

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
	node_type* _min;
	node_type* _max;
	node_type* _root;
	value_compare _comp;
	size_type _size;

	/* ------------------------------------------------------------------------- */

public:
	tree(value_compare const& comp, allocator_type const& alloc) :
		_alloc(alloc),
		_nil(this->__make_nil()),
		_min(this->_nil),
		_max(this->_nil),
		_root(this->_nil),
		_comp(comp),
		_size(0)
	{
	}

	template< class _Value, class _Compare, class _Alloc >
	tree(tree< _Value, _Compare, _Alloc > const& x) :
		_alloc(),
		_nil(),
		_min(),
		_max(),
		_root(),
		_comp(),
		_size()
	{
		*this = x;
	}

	tree& operator=(tree const& x)
	{
		if (this != &x)
		{
			this->clear();
			this->_root = this->__deep_copy(x, x._root, this->_nil);
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
	node_type* nil() const
	{
		return this->_nil;
	}

	node_type* root() const
	{
		return this->_root;
	}

	node_type* min() const
	{
		return this->_min;
	}

	node_type* max() const
	{
		return this->_max;
	}

	value_compare const& comp() const
	{
		return this->_comp;
	}

	size_type size() const
	{
		return this->_size;
	}

	/* ------------------------------------------------------------------------- */

public:
	ft::pair< iterator, bool > insert(value_type const& val)
	{
		node_type* node;
		node_type* inserted_node;

		inserted_node = 0;
		node = this->__insert(val, this->_nil, this->_root, inserted_node);
		this->_root = node;
		if (inserted_node != 0)
		{
			if (this->_min->is_nil() || this->_comp(val, this->_min->pair))
				this->_min = inserted_node;
			if (this->_max->is_nil() || this->_comp(this->_max->pair, val))
				this->_max = inserted_node;
			this->__update_nil();
		}
		return ft::make_pair(iterator(inserted_node), inserted_node != 0);
	}

	void clear()
	{
		this->__release(this->_root);
		this->_size = 0;
		this->_root = this->_nil;
		this->_min = this->_root;
		this->_max = this->_root;
		this->__update_nil();
	}

	template< class _Value, class _Compare, class _Alloc >
	void swap(tree< _Value, _Compare, _Alloc >& x)
	{
		std::swap(this->_comp, x._comp);
		std::swap(this->_root, x._root);
		std::swap(this->_min, x._min);
		std::swap(this->_max, x._max);
		std::swap(this->_size, x._size);
		std::swap(this->_alloc, x._alloc);
		std::swap(this->_nil, x._nil);
	}

	/* ------------------------------------------------------------------------- */

public:
	allocator_type get_allocator() const
	{
		return this->_alloc;
	}

	/* ------------------------------------------------------------------------- */

private:
	template< class _Value, class _Compare, class _Alloc >
	node_type* __deep_copy(tree< _Value, _Compare, _Alloc > const& origin, node_type const* node, node_type* parent)
	{
		node_type* new_node;

		if (node->is_nil())
			return this->nil();

		new_node = this->__make_node(node->pair);

		new_node->left = this->__deep_copy(origin, node->left, new_node);
		if (node->left == origin.min()) // TODO test if this works
			this->_min = new_node->left;
		new_node->right = this->__deep_copy(origin, node->right, new_node);
		if (node->right == origin.max()) // TODO test if this works
			this->_max = new_node->right;
		new_node->parent = parent;
		new_node->height = node->height;
		return new_node;
	}

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

	node_type* __insert(value_type const& value, node_type* parent, node_type* node, node_type*& inserted_node)
	{
		if (node->is_nil())
		{
			++this->_size;
			inserted_node = this->__make_node(value);
			inserted_node->parent = parent;
			return inserted_node;
		}
		if (this->_comp(value, node->pair))
			node->left = this->__insert(value, node, node->left, inserted_node);
		else if (this->_comp(node->pair, value))
			node->right = this->__insert(value, node, node->right, inserted_node);
		else
		{
			inserted_node = 0;
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

			// TODO wtf is that???
			node = this->max();
			node->pair = this->max()->pair;
			node->left = this->__remove(node->pair, node->left);
			// all of it!
		}
		this->__update_height(node);
		return this->__rebalance(node);
	}

	void __update_height(node_type* node)
	{
		int height_max = node->left->height;

		if (node->right->height > height_max)
			height_max = node->right->height;
		node->height = height_max + 1;
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

		node->left = center;
		left->right = node;

		if (!center->is_nil())
			center->parent = node;

		left->parent = node->parent;
		node->parent = left;

		this->__update_height(node);
		this->__update_height(left);
		return left;
	}

	node_type* __rotate_left(node_type* node)
	{
		node_type* right = node->right;
		node_type* center = right->left;

		node->right = center;
		right->left = node;

		if (!center->is_nil())
			center->parent = node;

		right->parent = node->parent;
		node->parent = right;

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

	void __update_nil()
	{
		this->_nil->left = this->_max;
		this->_nil->right = this->_min;
	}

	static int __abs(int a)
	{
		return (a < 0) ? -a : a;
	}
};

} // namespace avl
} // namespace ft
