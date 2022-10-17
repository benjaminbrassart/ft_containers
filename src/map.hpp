/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/17 14:36:03 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/avl_tree.hpp"
#include "private/tree_node.hpp"
#include "private/tree_iterator.hpp"

#include "iterator.hpp"
#include "utils.hpp"

#include <functional>
#include <memory>
#include <stdexcept>

namespace ft
{
template<
	class Key,
	class T,
	class Compare = std::less< Key >,
	class Alloc = std::allocator< ft::pair< Key const, T > >
>
class map
{

/* ------------------------------------------------------------------------- */

private:
	typedef ft::avl::tree_node< ft::pair< Key const, T > > node_type;

	// https://alp.developpez.com/tutoriels/templaterebinding/
	// https://cplusplus.com/reference/memory/allocator/rebind/
	// keep the same allocator object, with a difference generic type
	typedef typename Alloc::template rebind< node_type >::other node_allocator_type;

/* ------------------------------------------------------------------------- */

public:
	class value_compare;

	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair< key_type const, mapped_type > value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef ft::avl::tree_iterator< value_type, node_type > iterator;
	typedef ft::avl::tree_iterator< value_type const, node_type const > const_iterator;
	typedef ft::reverse_iterator< iterator > reverse_iterator;
	typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
	typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
	typedef typename allocator_type::size_type size_type;

private:
	typedef ft::avl::tree< value_type, value_compare, node_allocator_type > tree_type;

/* ------------------------------------------------------------------------- */

private:
	allocator_type _alloc;
	key_compare _kcomp;

	// value_compare _vcomp;
	// node_type* _nil;
	// node_type* _root;
	// node_type* _min;
	// node_type* _max;
	// size_type _size;

	tree_type _tree;

/* ------------------------------------------------------------------------- */

public:
	explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_kcomp(comp),
		// _nil(this->__make_nil()),
		// _root(this->_nil),
		// _min(this->_nil),
		// _max(this->_nil),
		// _size(0)
		_tree(value_compare(comp), node_allocator_type(alloc))
	{
	}

	template< class InputIterator >
	map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_kcomp(comp),
		// _vcomp(value_compare(comp)),
		// _nil(this->__make_nil()),
		// _root(this->_nil),
		// _min(this->_nil),
		// _max(this->_nil),
		// _size(0)
		_tree(value_compare(comp), node_allocator_type(alloc))
	{
		this->insert(first, last);
	}

	template<
		class _Key,
		class _T,
		class _Compare,
		class _Alloc
	>
	map(map< _Key, _T, _Compare, _Alloc > const& x) :
		_alloc(x.get_allocator()),
		_kcomp(x.key_comp()),
		// _vcomp(x.value_comp()),
		// _nil(this->__make_nil()),
		// _root(this->_nil),
		// _min(this->_nil),
		// _max(this->_nil),
		// _size(0)
		_tree(value_compare(x._kcomp), node_allocator_type(x._alloc))
	{
		this->insert(x.begin(), x.end());
	}

	// TODO adapt for avl_tree class
	template<
		class _Key,
		class _T,
		class _Compare,
		class _Alloc
	>
	map& operator=(map< _Key, _T, _Compare, _Alloc > const& rhs)
	{
		if (this != &rhs)
		{
			this->clear();
			this->_kcomp = rhs._kcomp;
			this->_vcomp = rhs._vcomp;
			this->insert(rhs.begin(), rhs.end());
		}
		return *this;
	}

	~map()
	{
		this->clear();
	}

/* ------------------------------------------------------------------------- */

public:
	iterator begin()
	{
		return iterator(this->_tree._min);
	}

	const_iterator begin() const
	{
		return const_iterator(this->_tree._min);
	}

	iterator end()
	{
		return iterator(this->_tree._nil);
	}

	const_iterator end() const
	{
		return const_iterator(this->_tree._nil);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(this->end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(this->end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(this->begin());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(this->begin());
	}

/* ------------------------------------------------------------------------- */

public:
	bool empty() const
	{
		return this->size() == 0;
	}

	size_type size() const
	{
		return this->_tree.size();
	}

	size_type max_size() const
	{
		return this->_tree.get_allocator().max_size();
	}

/* ------------------------------------------------------------------------- */

public:
	// https://legacy.cplusplus.com/reference/map/map/operator[]/
	// this is incredibly ugly and i love it, thanks cplusplus.com
	mapped_type& operator[](key_type const& key)
	{
		return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
	}

/* ------------------------------------------------------------------------- */

public:
	// TODO test
	ft::pair< iterator, bool > insert(value_type const& val)
	{
		// node_type* node = this->_root;
		// node_type* prev = this->_nil;
		// node_type* new_node;

		// while (!node->is_nil())
		// {
		// 	prev = node;
		// 	if (this->value_comp()(val, node->pair)) // should go to the left, e.g. is less than
		// 		node = node->left;
		// 	else if (this->value_comp()(node->pair, val)) // should go to the right, e.g. is greater than
		// 		node = node->right;
		// 	else // keys are considered equal, therefore no insertion and we return immediately
		// 		return ft::make_pair(iterator(node), false);
		// }

		// new_node = this->__make_node(val);

		// if (prev->is_nil()) // map is empty, replace root
		// {
		// 	this->_root = new_node;
		// 	this->_nil->left = this->_root;
		// 	this->_nil->right = this->_root;
		// 	this->_min = this->_root;
		// 	this->_max = this->_root;
		// 	++this->_size;
		// 	return ft::make_pair(iterator(this->_root), true);
		// }

		TODO();
	}

	iterator insert(iterator position, value_type const& val)
	{
		(void)position;
		return this->insert(val).first;
	}

	template< class InputIterator >
	void insert(InputIterator first, InputIterator last)
	{
		for (InputIterator it = first; it != last; ++it)
			this->insert(*it);
	}

	void erase(iterator position)
	{
		if (position == this->end())
			return;
		TODO();
	}

	// TODO test implementation
	size_type erase(key_type const& k)
	{
		iterator position = this->find(k);

		if (position != this->end())
		{
			this->erase(position);
			return 1;
		}
		return 0;
	}

	void erase(iterator first, iterator last)
	{
		// if (first == this->begin() && last == this->end())
		// {
		// 	this->__avl_release(this->_root);
		// 	return;
		// }
		// for (iterator it = first; first != last; ++first)
		// 	this->erase(it);
		TODO();
	}

	// TODO test implementation
	void swap(map& x)
	{
		// swap tree
		tree_type x_tree = x._tree;

		x._tree = this->_tree;
		this->_tree = x_tree;

		// swap key_comp
		key_compare x_kcomp = x._kcomp;

		x._kcomp = this->_kcomp;
		this->_kcomp = x_kcomp;
	}

	// TODO test implementation
	void clear()
	{
		this->erase(this->begin(), this->end());
	}

/* ------------------------------------------------------------------------- */

public:
	key_compare key_comp() const
	{
		return this->_kcomp;
	}

	value_compare value_comp() const
	{
		return this->_vcomp;
	}

/* ------------------------------------------------------------------------- */

public:
	iterator find(key_type const& k)
	{
		node_type* iter = this->_root;

		while (!iter->is_nil())
		{
			if (this->key_comp()(k, iter->pair.first))
				iter = iter->left;
			else if (this->key_comp()(iter->pair.first, k))
				iter = iter->right;
			else
				break;
		}

		return iterator(iter);
	}

	const_iterator find(key_type const& k) const
	{
		node_type* iter = this->_root;

		while (!iter->is_nil())
		{
			if (this->key_comp()(k, iter->pair.first))
				iter = iter->left;
			else if (this->key_comp()(iter->pair.first, k))
				iter = iter->right;
			else
				break;
		}

		return const_iterator(iter);
	}

	// TODO test implementation
	size_type count(key_type const& k) const
	{
		if (this->find(k) == this->end())
			return 0;
		return 1;
	}

	iterator lower_bound(key_type const& k)
	{
		(void)k;
		TODO();
	}

	const_iterator lower_bound(key_type const& k) const
	{
		(void)k;
		TODO();
	}

	iterator upper_bound(key_type const& k)
	{
		(void)k;
		TODO();
	}

	const_iterator upper_bound(key_type const& k) const
	{
		(void)k;
		TODO();
	}

	ft::pair< const_iterator, const_iterator > equal_range(key_type const& k) const
	{
		return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
	}

	ft::pair< iterator, iterator > equal_range(key_type const& k)
	{
		return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
	}

/* ------------------------------------------------------------------------- */

public:
	allocator_type get_allocator() const
	{
		return this->_alloc;
	}

/* ------------------------------------------------------------------------- */

private:
	// node_type* __make_nil()
	// {
	// 	node_type* node = this->_nodealloc.allocate(1);
	// 	node_type tmp;

	// 	tmp.left = this->_nil;
	// 	tmp.right = this->_nil;

	// 	this->_nodealloc.construct(node, tmp);
	// 	return node;
	// }

	// node_type* __make_node(value_type const& value)
	// {
	// 	node_type* node = this->_nodealloc.allocate(1);
	// 	node_type tmp(this->_nil, value);

	// 	tmp.left = this->_nil;
	// 	tmp.right = this->_nil;

	// 	this->_nodealloc.construct(node, tmp);
	// 	return node;
	// }

	// void __avl_release(node_type* node)
	// {
	// 	if (node->is_nil())
	// 		return;
	// 	this->__avl_release(node->left);
	// 	this->__avl_release(node->right);
	// 	this->_nodealloc.destroy(node);
	// 	this->_nodealloc.deallocate(node, 1);
	// }

	// node_type* __rotate_right(node_type* node)
	// {
	// 	node_type* left = node->left;
	// 	node_type* center = left->right;

	// 	left->right = node;
	// 	node->left = center;
	// 	this->__update_height(node);
	// 	this->__update_height(left);
	// 	return left;
	// }

	// node_type* __rotate_left(node_type* node)
	// {
	// 	node_type* right = node->right;
	// 	node_type* center = right->left;

	// 	right->left = node;
	// 	node->right = center;
	// 	this->__update_height(node);
	// 	this->__update_height(right);
	// 	return right;
	// }

	// void __update_height(node_type* node)
	// {
	// 	node->height = std::max(
	// 		node->left->height,
	// 		node->right->height
	// 	) + 1;
	// }

	// node_type* __rebalance(node_type* node)
	// {
	// 	int balance = node->get_balance();
	// 	int balance_next;

	// 	if (balance > 1)
	// 	{
	// 		balance_next = node->left->get_balance();
	// 		if (balance_next < 0)
	// 			node->left = this->__rotate_left(node->left);
	// 		return this->__rotate_right(node);
	// 	}
	// 	else if (balance < -1)
	// 	{
	// 		balance_next = node->right->get_balance();
	// 		if (balance_next > 0)
	// 			node->right = this->__rotate_right(node->right);
	// 		return __rotate_left(node);
	// 	}
	// 	return node;
	// }

	// bool __is_balanced(node_type* node)
	// {
	// 	int const balance = node->get_balance();

	// 	return balance >= -1 && balance <= 1;
	// }

	// bool __check_balance(node_type* node)
	// {
	// 	return (this->__is_balanced(node))
	// 		&& (this->__check_balance(node->left))
	// 		&& (this->__check_balance(node->right));
	// }

/* ------------------------------------------------------------------------- */

public:
	// https://legacy.cplusplus.com/reference/map/map/value_comp/
	class value_compare : public std::binary_function< value_type, value_type, bool >
	{
		friend class map;

	private:
		Compare _comp;

		value_compare(Compare comp) :
			_comp(comp)
		{
		}

	public:
		bool operator()(value_type const& x, value_type const& y)
		{
			return this->_comp(x.first, y.first);
		}
	};
}; // class map

/* ------------------------------------------------------------------------- */

template< class Key, class T, class Compare, class Alloc >
bool operator==(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return (&lhs == &rhs) || (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); // TODO use Compare object
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return &lhs == &rhs || ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); // TODO use Compare object
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return !(rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return (rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return !(lhs < rhs);
}
} // namespace ft

/* ------------------------------------------------------------------------- */

namespace std
{
template< class Key, class T, class Compare, class Alloc >
void swap(ft::map< Key, T, Compare, Alloc >& lhs, ft::map< Key, T, Compare, Alloc >& rhs)
{
	lhs.swap(rhs);
}
} // namespace std
