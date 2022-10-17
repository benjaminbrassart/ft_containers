/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/17 17:08:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "private/tree_iterator.hpp"
#include "private/tree_node.hpp"

namespace ft
{
namespace avl
{

template<
	class Value,
	class Compare,
	class Alloc
>
class tree
{
private:
	typedef Value value_type;
	typedef Compare value_compare;
	typedef ft::avl::tree_node< value_type > node_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::size_type size_type;

private:
	allocator_type _alloc;
	node_type* _nil;
	node_type* _root;
	node_type* _min;
	node_type* _max;
	value_compare _comp;
	size_type _size;

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

	~tree(){

	}

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

public:
	allocator_type get_allocator()
	{
		return this->_alloc;
	}

private:

};

} // namespace avl
} // namespace ft
