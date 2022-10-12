/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/12 02:27:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree.hpp"
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
	class Compare = less< Key >,
	class Alloc = std::allocator< ft::avl::tree_node< ft::pair< Key, T > > >
>
class map
{
	public:
	/** The first template parameter */
	typedef Key key_type;
	/** The second template parameter */
	typedef T mapped_type;
	typedef ft::pair< key_type const, mapped_type > value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef ft::avl::tree_iterator< value_type > iterator;
	typedef ft::avl::tree_iterator< value_type > const const_iterator;
	typedef ft::reverse_iterator< iterator > reverse_iterator;
	typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
	typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
	typedef typename allocator_type::size_type size_type;

	// https://legacy.cplusplus.com/reference/map/map/value_comp/
	class value_compare : ft::binary_function< value_type, value_type, bool >
	{
		friend class map;

		protected:
		Compare _comp;

		value_compare(Compare comp) :
			_comp(comp)
		{
		}

		public:
		bool operator()(value_type const& first, value_type const& second)
		{
			return this->_comp(first, second);
		}
	}

	private:
	typedef ft::avl::tree< value_type, Compare, Alloc > tree_type;

	private:
	ft::avl::tree< value_type, Compare, Alloc > _tree;
	key_compare _kcomp;
	value_compare _vcomp;
	allocator_type _alloc;

	public:
	explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
		_tree(),
		_kcomp(comp),
		_vcomp(value_compare(comp)),
		_alloc(alloc)
	{
	}

	template< class InputIterator >
	map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
		_tree(),
		_kcomp(comp),
		_vcomp(value_compare(comp)),
		_alloc(alloc)
	{
		for (InputIterator it = first; it != last; ++it)
			this->insert(*it);
	}

	map(map const& x) :
		_tree(),
		_kcomp(x._kcomp),
		_vcomp(x._vcomp),
		_alloc(x._alloc)
	{
		for (iterator it = x.begin(); it != x.end(); ++it)
			this->insert(*it);
	}

	~map()
	{
		this->clear();
	}

	map& operator=(map const& rhs)
	{
		if (this != &rhs)
		{
			this->clear();
			for (iterator it = rhs.begin(); it != rhs.end(); ++it)
				this->insert(*it);
		}
		return *this;
	}

	public:
	iterator begin()
	{
		return iterator(this->_tree._min);
	}

	const_iterator begin() const
	{
		return const_iterator(this->_tree._min);
	}

	// TODO test implementation
	iterator end()
	{
		return iterator(this->_tree._nil_node);
	}

	// TODO test implementation
	const_iterator end() const
	{
		return const_iterator(this->_tree._nil_node);
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

	public:
	bool empty() const
	{
		return this->size() == 0;
	}

	size_type size() const
	{
		return this->_tree._size;
	}

	size_type max_size() const
	{
		return this->get_allocator().max_size();
	}

	public:
	// TODO provide implementation
	// never throws exception, always add element (wtf?)
	mapped_type& operator[](key_type const& key);

	public:
	// TODO provide implementation
	ft::pair< iterator, bool > insert(value_type const& val)
	{
		// node_type* node = this->_root;

		// while (node != NULL)
		// {
		// 	if (!this->key_comp()(k, node->_value))
		// 		node = node->right;
		// 	else if (!this->key_comp()(node->_value, k))
		// 		node = node->left;
		// 	else
		// 	{
		// 		node->value.second = val.second;
		// 		return ft::pair<iterator, bool>(iterator(node), false);
		// 	}
		// }
		// return iterator(node);
		throw 0; // TODO
	}

	// TODO provide implementation
	iterator insert(iterator position, value_type const& val);

	template< class InputIterator >
	void insert(InputIterator first, InputIterator last)
	{
		for (InputIterator it = first; it != last; ++it)
			this->insert(*it);
	}

	// TODO provide implementation
	void erase(iterator position);

	// TODO provide implementation
	size_type erase(key_type const& k);

	// TODO provide implementation
	void erase(iterator first, iterator last)
	{
		for (iterator it = first; first != last; ++first)
			this->erase(it);
	}

	// TODO test implementation
	void swap(map& x)
	{
		// swap trees
		tree_type x_tree = x._tree;

		x._tree = this->_tree;
		this->_tree = x_tree;

		key_compare x_kcomp = x._kcomp;

		x._kcomp = this->_kcomp;
		this->_kcomp = x_kcomp;

		value_compare x_vcomp = x._vcomp;

		x._vcomp = this->_vcomp;
		this->_vcomp = x_vcomp;
	}

	// TODO test implementation
	void clear()
	{
		this->release(this->_root);
		this->_size = 0;
	}

	public:
	key_compare key_comp() const
	{
		return this->_kcomp;
	}

	value_compare value_comp() const
	{
		return this->_vcomp;
	}

	public:
	// TODO test implementation
	iterator find(key_type const& k)
	{
		// node_type* node = this->_root;

		// while (node != NULL)
		// {
		// 	if (!this->key_comp()(k, node->_value))
		// 		node = node->right;
		// 	else if (!this->key_comp()(node->_value, k))
		// 		node = node->left;
		// 	else
		// 		break;
		// }
		// return iterator(node);
		throw 0; // TODO
	}

	// TODO test implementation
	const_iterator find(key_type const& k) const
	{
		// node_type* node = this->_root;

		// while (node != NULL)
		// {
		// 	if (!this->key_comp()(k, node->_value))
		// 		node = node->right;
		// 	else if (!this->key_comp()(node->_value, k))
		// 		node = node->left;
		// 	else
		// 		break;
		// }
		// return iterator(node);
		throw 0; // TODO
	}

	// TODO test implementation
	size_type count(key_type const& k) const
	{
		if (this->find(k) == NULL)
			return 0;
		return 1;
	}

	// TODO provide implementation
	iterator lower_bound(key_type const& k);

	// TODO provide implementation
	const_iterator lower_bound(key_type const& k) const;

	// TODO provide implementation
	iterator upper_bound(key_type const& k);

	// TODO provide implementation
	const_iterator upper_bound(key_type const& k) const;

	// TODO provide implementation
	ft::pair< const_iterator, const_iterator > equal_range(key_type const& k) const;

	// TODO provide implementation
	ft::pair< iterator, iterator > equal_range(key_type const& k);

	public:
	allocator_type get_allocator() const
	{
		return this->_alloc;
	}

	private:
	template< class _Alloc >
	static node_type* insert(T const& value, node_type* node, _Alloc const& alloc)
	{
		if (node == NULL)
			return alloc.construct(alloc.allocate(1), value);
		if (value < node->value) // TODO use key_compare
			node->left = insert(value, node->left, alloc);
		else if (value > node->value) // TODO use key_compare
			node->right = insert(value, node->right, alloc);
		else
			return node;
		update_height(node);
		return rebalance(node);
	}

	// static node_type* remove(T const& value, node_type* node)
	// {
	// }

	// static node_type* search(T const& value, node_type* node)
	// {
	// 	if (node == NULL)
	// 		return NULL;
	// 	if (value > node->value) // TODO use key_compare
	// 		return search(value, node->right);
	// 	if (value < node->value) // TODO use key_compare
	// 		return search(value, node->left);
	// 	return node;
	// }

	// static void update_height(node_type* node)
	// {
	// 	int h_left = get_height(node->left);
	// 	int h_right = get_height(node->right);
	// 	int h_max = (h_left > h_right) ? h_left : h_right;

	// 	node->height = h_max + 1;
	// }

	// static node_type* rebalance(node_type* node)
	// {
	// 	int balance = get_balance(node);
	// 	int balance_sub; // TODO remove

	// 	if (balance > 1)
	// 	{
	// 		balance_sub = get_balance(node->left);
	// 		if (balance_sub < 0)
	// 			node->left = rotate_left(node->left);
	// 		return rotate_right(node);
	// 	}
	// 	else if (balance < -1)
	// 	{
	// 		balance_sub = get_balance(node->right);
	// 		if (balance_sub < 0)
	// 			node->right = rotate_left(node->right);
	// 		return rotate_left(node);
	// 	}
	// 	return node;
	// }

	// static node_type* rotate_right(node_type* node)
	// {
	// 	node_type* left = node->left;
	// 	node_type* center = left->right;

	// 	left->right = node;
	// 	node->left = center;
	// 	update_height(node);
	// 	update_height(left);
	// 	return left;
	// }

	// static node_type* rotate_left(node_type* node)
	// {
	// 	node_type* right = node->right;
	// 	node_type* center = right->left;

	// 	right->left = node;
	// 	node->right = center;
	// 	update_height(node);
	// 	update_height(right);
	// 	return right;
	// }

	// static int get_balance(node_type* node)
	// {
	// 	if (node == NULL)
	// 		return 0;
	// 	return get_height(node->left) - get_height(node->right);
	// }

	// static int get_height(node_type* node)
	// {
	// 	if (node == NULL)
	// 		return 0;
	// 	return node->height;
	// }

	// template< class _Alloc >
	// static void release(node_type* node, _Alloc const& alloc)
	// {
	// 	if (node == NULL)
	// 		return ;
	// 	release(node->left);
	// 	release(node->right);
	// 	alloc.destroy(node);
	// 	alloc.deallocate(node, 1);
	// }

	// static value_type& get_max(node_type* node)
	// {
	// 	if (node->right != NULL)
	// 		return get_max(node->right);
	// 	return node->value;
	// }
}; // class map

template< class Key, class T, class Compare, class Alloc >
bool operator==(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return (&lhs == &rhs) || (lhs.size() == rhs.size() && ft:equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); // TODO use Compare object
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

namespace std
{
template< class Key, class T, class Compare, class Alloc >
void swap(ft::map< Key, T, Compare, Alloc >& lhs, ft::map< Key, T, Compare, Alloc >& rhs)
{
	lhs.swap(rhs);
}
} // namespace std
