/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:45:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/03 09:43:10 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/avl_tree.hpp"
#include "private/tree_iterator.hpp"
#include "private/tree_node.hpp"

#include "iterator.hpp"
#include "utils.hpp"

#include <functional>
#include <memory>
#include <stdexcept>

namespace ft
{
template< class Key, class T, class Compare = std::less< Key >, class Alloc = std::allocator< ft::pair< const Key, T > > >
class map
{
	/* ------------------------------------------------------------------------- */

private:
	typedef ft::avl::tree_node< ft::pair< const Key, T > > node_type;

	// https://alp.developpez.com/tutoriels/templaterebinding/
	// https://cplusplus.com/reference/memory/allocator/rebind/
	// keep the same allocator object, with a difference generic type
	typedef typename Alloc::template rebind< node_type >::other node_allocator_type;

	/* ------------------------------------------------------------------------- */

public:
	class value_compare;

	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair< const key_type, mapped_type > value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef ft::tree_iterator< value_type, node_type > iterator;
	typedef ft::tree_iterator< value_type const, node_type const > const_iterator;
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
	tree_type _tree;

	/* ------------------------------------------------------------------------- */

public:
	explicit map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_kcomp(comp),
		_tree(value_compare(comp), node_allocator_type(alloc))
	{
	}

	template< class InputIterator >
	map(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_kcomp(comp),
		_tree(value_compare(comp), node_allocator_type(alloc))
	{
		this->insert(first, last);
	}

	map(map const& x) :
		_alloc(x.get_allocator()),
		_kcomp(x.key_comp()),
		_tree(x._tree)
	{
	}

	map& operator=(map const& rhs)
	{
		if (this != &rhs)
		{
			this->_kcomp = rhs._kcomp;
			this->_tree = rhs._tree;
		}
		return *this;
	}

public:
	~map()
	{
		// do NOT clear here, everything is allocated on the stack!
	}

	/* ------------------------------------------------------------------------- */

public:
	iterator begin()
	{
		return iterator(this->_tree.min());
	}

	const_iterator begin() const
	{
		return const_iterator(this->_tree.min());
	}

	iterator end()
	{
		return iterator(this->_tree.nil());
	}

	const_iterator end() const
	{
		return const_iterator(this->_tree.nil());
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
	ft::pair< iterator, bool > insert(value_type const& val)
	{
		return this->_tree.insert(val);
	}

	// TODO make use of position for optimization
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
		this->_tree.remove(position.base());
	}

	size_type erase(key_type const& k)
	{
		iterator position = this->find(k);

		if (position == this->end())
			return 0;
		this->erase(position);
		return 1;
	}

	void erase(iterator first, iterator last)
	{
		if (first == this->begin() && last == this->end())
		{
			// special case: trying to erase the whole container,
			// do not bother rotating nodes
			this->clear();
			return;
		}

		iterator it = first;
		iterator fast;

		while (it != last)
		{
			fast = it;
			++fast;
			this->erase(it);
			it = fast;
		}
	}

	void swap(map& x)
	{
		this->_tree.swap(x._tree);
		std::swap(this->_kcomp, x._kcomp);
	}

	void clear()
	{
		this->_tree.clear();
	}

	/* ------------------------------------------------------------------------- */

public:
	key_compare key_comp() const
	{
		return this->_kcomp;
	}

	value_compare value_comp() const
	{
		return this->_tree.comp();
	}

	/* ------------------------------------------------------------------------- */

public:
	iterator find(key_type const& k)
	{
		return this->__find< iterator >(k);
	}

	const_iterator find(key_type const& k) const
	{
		return this->__find< const_iterator >(k);
	}

	size_type count(key_type const& k) const
	{
		return (this->find(k) == this->end()) ? 0 : 1;
	}

	iterator lower_bound(key_type const& k)
	{
		return this->__find_bound< iterator >(k, true);
	}

	const_iterator lower_bound(key_type const& k) const
	{
		return this->__find_bound< const_iterator >(k, true);
	}

	iterator upper_bound(key_type const& k)
	{
		return this->__find_bound< iterator >(k, false);
	}

	const_iterator upper_bound(key_type const& k) const
	{
		return this->__find_bound< const_iterator >(k, false);
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
	template< class Iterator >
	Iterator __find(key_type const& k) const
	{
		node_type* iter = this->_tree.root();

		while (!iter->is_nil())
		{
			if (this->key_comp()(k, iter->pair.first))
				iter = iter->left;
			else if (this->key_comp()(iter->pair.first, k))
				iter = iter->right;
			else
				break;
		}
		return Iterator(iter);
	}

	template< class Iterator >
	Iterator __find_bound(key_type const& k, bool is_lower) const
	{
		node_type* node;
		node_type* slow;

		node = this->_tree.root();
		slow = this->_tree.nil();
		while (!node->is_nil())
		{
			if ((is_lower) ? (!this->key_comp()(node->pair.first, k)) : (this->key_comp()(k, node->pair.first)))
			{
				slow = node;
				node = node->left;
			}
			else
				node = node->right;
		}
		return Iterator(slow);
	}

	/* ------------------------------------------------------------------------- */

public:
	// https://legacy.cplusplus.com/reference/map/map/value_comp/
	class value_compare : public std::binary_function< value_type, value_type, bool >
	{
		friend class map;

	protected:
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
	return (&lhs == &rhs) || ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<(map< Key, T, Compare, Alloc > const& lhs, map< Key, T, Compare, Alloc > const& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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

namespace ft
{
template< class Key, class T, class Compare, class Alloc >
void swap(ft::map< Key, T, Compare, Alloc >& lhs, ft::map< Key, T, Compare, Alloc >& rhs)
{
	lhs.swap(rhs);
}
} // namespace ft
