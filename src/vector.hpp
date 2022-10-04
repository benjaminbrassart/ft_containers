/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 02:00:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/04 15:17:54 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include "utils.hpp"

#include <memory>
#include <stdexcept>

namespace ft
{

// TODO add documentation
template<
	class T,
	class Alloc = std::allocator< T >
>
class vector
{

/* ------------------------------------------------------------------------- */

public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef ft::reverse_iterator< iterator > reverse_iterator;
	typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
	typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
	typedef typename allocator_type::size_type size_type;

/* ------------------------------------------------------------------------- */

private:
	allocator_type _alloc;
	pointer _data;
	size_type _size;
	size_type _capacity;

/* ------------------------------------------------------------------------- */

public:
	// TODO test implementation
	explicit vector(allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
	}

	// TODO test implementation
	explicit vector(size_type n, value_type const& val = value_type(), allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
		this->assign(n, val);
	}

	// TODO test implementation
	template< class InputIterator >
	vector(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
		this->assign(first, last);
	}

	// TODO test implementation
	vector(vector const& x) :
		_alloc(x._alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
		this->assign(x.begin(), x.end());
	}

	// TODO test implementation
	vector& operator=(vector const& x)
	{
		if (&x != this)
			this->assign(x.begin(), x.end());
		return *this;
	}

	// TODO test implementation
	~vector()
	{
		this->clear();
		this->_alloc.deallocate(this->_data, this->capacity());
	}

/* ------------------------------------------------------------------------- */

public:
	iterator begin()
	{
		return this->_data;
	}

	const_iterator begin() const
	{
		return this->_data;
	}

	iterator end()
	{
		return this->_alloc.address(this->operator[](this->size()));
	}

	const_iterator end() const
	{
		return this->_alloc.address(this->_data[this->_size]);
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
	size_type size() const
	{
		return this->_size;
	}

	size_type max_size() const
	{
		return this->_alloc.max_size();
	}

	// TODO test implementation
	void resize(size_type n, value_type val = value_type())
	{
		size_type const size = this->size();
		size_type i;

		this->reserve(n);
		if (n > size)
		{
			for (i = size; i < n; ++i)
				this->_alloc.construct(this->_alloc.address(this->_data[i]), val);
		}
		else if (n < size)
		{
			for (i = n; i < size; ++i)
				this->_alloc.destroy(this->_alloc.address(this->_data[i]));
		}
		this->_size = n;
	}

	size_type capacity() const
	{
		return this->_capacity;
	}

	bool empty() const
	{
		return this->size() == 0;
	}

	// TODO test implementation
	void reserve(size_type n)
	{
		if (this->capacity() >= n)
			return ;

		size_type new_capacity = n * 2;
		pointer new_data = this->_alloc.allocate(new_capacity);

		for (size_type i = 0; i < this->size(); ++i)
		{
			this->_alloc.construct(this->_alloc.address(new_data[i]), this->_data[i]);
			this->_alloc.destroy(this->_alloc.address(this->_data[i]));
		}

		this->_alloc.deallocate(this->_data, this->capacity());
		this->_data = new_data;
		this->_capacity = new_capacity;
	}

/* ------------------------------------------------------------------------- */

public:
	reference operator[](size_type n)
	{
		return this->_data[n];
	}

	const_reference operator[](size_type n) const
	{
		return this->_data[n];
	}

	// TODO test implementation
	reference at(size_type n)
	{
		if (n >= this->size())
			throw std::out_of_range(__PRETTY_FUNCTION__);
		return this->_data[n];
	}

	// TODO test implementation
	const_reference at(size_type n) const
	{
		if (n >= this->size())
			throw std::out_of_range(__PRETTY_FUNCTION__);
		return this->_data[n];
	}

	reference front()
	{
		return *(this->begin());
	}

	const_reference front() const
	{
		return *(this->begin());
	}

	reference back()
	{
		return *(this->rbegin());
	}

	const_reference back() const
	{
		return *(this->rbegin());
	}

/* ------------------------------------------------------------------------- */

public:
	// TODO test implementation
	// TODO optimize with only 1 loop
	template< class InputIterator >
	void assign(InputIterator first, InputIterator last)
	{
		this->__dispatch_assign(first, last, ft::is_integral<InputIterator>());
	}

	// TODO add dispatcher
	// TODO test implementation
	// TODO optimize with only 1 loop
	void assign(size_type n, value_type const& val)
	{
		this->__assign_fill(n, val);
	}

	// TODO test implementation
	void push_back(value_type const& val)
	{
		size_type& size = this->_size;

		this->reserve(size + 1);
		this->get_allocator().construct(this->_data + size, val);
		++size;
	}

	// TODO test implementation
	void pop_back()
	{
		if (this->empty())
			return ;
		this->resize(this->size() - 1);
	}

	// TODO test implementation
	iterator insert(iterator position, value_type const& val)
	{
		return this->__insert_fill(position, 1, val);
	}

	// TODO test implementation
	void insert(iterator position, size_type n, value_type const& val)
	{
		this->__insert_fill(position, n, val);
	}

	// TODO test implementation
	// NOTE: memory usage might be high for this function to avoid
	// inserting elements one by one
	template< class InputIterator >
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		this->__dispatch_insert(position, first, last, ft::is_integral<InputIterator>());
	}

	// TODO test implementation
	iterator erase(iterator position)
	{
		return this->__erase(position - this->_data, 1);
	}

	// [ 1 2 3 4 5 ] //
	//     ^___^ del //
	// [ 1 5 ]       //
	//     ^  return //
	// TODO test implementation
	iterator erase(iterator first, iterator last)
	{
		return this->__erase(first - this->_data, last - first);
	}

	// TODO test implementation
	void swap(vector& x)
	{
		// swap data pointers
		pointer x_data = x._data;

		x._data = this->_data;
		this->_data = x_data;

		// swap sizes
		this->_size ^= x._size;
		x._size ^= this->_size;
		this->_size ^= x._size;

		// swap capacities
		this->_capacity ^= x._capacity;
		x._capacity ^= this->_capacity;
		this->_capacity ^= x._capacity;
	}

	// TODO test implementation
	void clear()
	{
		size_type const size = this->size();

		for (size_type n = 0; n < size; ++n)
			this->_alloc.destroy(this->_alloc.address(_data[n]));
		this->_size = 0;
	}

/* ------------------------------------------------------------------------- */

public:
	allocator_type get_allocator() const
	{
		return this->_alloc;
	}

/* ------------------------------------------------------------------------- */

private:
	iterator __move_right(iterator position, size_type n)
	{
		size_type const offset = (position - this->begin());
		iterator p;
		size_type i;

		this->reserve(this->size() + n);
		p = (this->begin() + offset);
		i = (this->end() - p);
		while (i > 0)
		{
			--i;
			this->get_allocator().construct(p + n + i, p[i]);
			this->get_allocator().destroy(p + i);
		}
		return p;
	}

	iterator __move_left(iterator position, size_type n)
	{
		for (size_type i = 0; i < n; ++i)
		{
			this->get_allocator().construct(position + i, *(position + i + n));
			this->get_allocator().destroy(position + i + n);
		}
		return position - n;
	}

	iterator __insert_fill(iterator position, size_type n, value_type const& val)
	{
		iterator p;

		if (position == this->begin() && this->empty())
		{
			this->assign(n, val);
			return this->begin();
		}
		if (position == this->end())
		{
			size_type const start_size = this->size();

			for (size_type i = 0; i < n; ++i)
				this->push_back(val);

			return this->begin() + start_size;
		}

		p = this->__move_right(position, n);

		for (size_type i = 0; i < n; ++i)
			this->get_allocator().construct(p + i, val);

		this->_size += n;
		return p;
	}

	template< class InputIterator >
	void __insert_range(iterator position, InputIterator first, InputIterator last)
	{
		if (position == this->begin() && this->empty())
		{
			this->assign(first, last);
			return ;
		}
		if (position == this->end())
		{
			for (InputIterator it = first; it != last; ++it)
				this->push_back(*it);
			return ;
		}

		vector< T, Alloc > v;

		for (InputIterator it = first; it != last; ++it)
			v.push_back(*it);

		size_type const size = v.size();
		size_type const offset = position - this->begin();

		this->__move_right(this->begin() + offset, size);

		for (size_type i = 0; i < size; ++i)
			this->get_allocator().construct(this->begin() + offset + i, v[i]);
		this->_size += size;
	}

	// if InputIterator is integral, insert via fill method (aka the same value for n elements)
	template< class InputIterator >
	void __dispatch_insert(iterator position, InputIterator first, InputIterator last, ft::true_type)
	{
		this->__insert_fill(position, first, last);
	}

	// if InputIterator is not integral, insert via range method (aka insert from first to last)
	template< class InputIterator >
	void __dispatch_insert(iterator position, InputIterator first, InputIterator last, ft::false_type)
	{
		this->__insert_range(position, first, last);
	}

	void __assign_fill(size_type n, value_type const& val)
	{
		this->clear();
		this->resize(n, val);
	}

	template< class InputIterator >
	void __assign_range(InputIterator first, InputIterator last)
	{
		this->clear();
		for (InputIterator it = first; it != last; ++it)
			this->push_back(*it);
	}

	template< class InputIterator >
	void __dispatch_assign(InputIterator first, InputIterator last, ft::true_type)
	{
		this->__assign_fill(first, last);
	}

	template< class InputIterator >
	void __dispatch_assign(InputIterator first, InputIterator last, ft::false_type)
	{
		this->__assign_range(first, last);
	}

	iterator __erase(size_type index, size_type width)
	{
		size_type const elems = this->size();

		for (size_type i = index; i < (elems - width); ++i)
		{
			this->get_allocator().destroy(this->_data + i);
			this->get_allocator().construct(this->_data + i, this->_data[i + width]);
			this->get_allocator().destroy(this->_data + i + width);
		}
		this->_size -= width;
		return this->_data + index;
	}
}; // class vector

/* ------------------------------------------------------------------------- */

template< class T, class Alloc >
bool operator==(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return (&lhs == &rhs) || (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin(), lhs.end()));
}

template< class T, class Alloc >
bool operator!=(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return !(lhs == rhs);
}

// TODO test implementation
template< class T, class Alloc >
bool operator<(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end());
}

// TODO test implementation
template< class T, class Alloc >
bool operator<=(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return !(rhs < lhs);
}

// TODO test implementation
template< class T, class Alloc >
bool operator>(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return rhs < lhs;
}

// TODO test implementation
template< class T, class Alloc >
bool operator>=(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return !(lhs < rhs);
}

// TODO test implementation
template< class T, class Alloc >
void swap(vector< T, Alloc >& x, vector< T, Alloc >& y)
{
	x.swap(y);
}

} // namespace ft
