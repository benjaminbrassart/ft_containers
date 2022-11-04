/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 02:00:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/04 22:43:18 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

#include <memory>
#include <stdexcept>

namespace ft
{

// TODO add documentation
/**
 * @tparam T the type of the stored objects
 * @tparam Alloc the type of allocator object, defaults to std::allocator< T >
 */
template< class T, class Alloc = std::allocator< T > >
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
	static size_type const MIN_SIZE = 64;

	allocator_type _alloc;
	pointer _data;
	size_type _size;
	size_type _capacity;

	/* ------------------------------------------------------------------------- */

public:
	/**
	 * Create an empty vector
	 *
	 * @param alloc allocator object, defaults to allocator_type
	 */
	explicit vector(allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
	}

	/**
	 * Create a vector of n elements
	 *
	 * @param n the number of elements to put in the vector
	 * @param val the value of each element, defaults to a default-constructed value
	 * @param alloc allocator object, defaults to allocator_type
	 */
	explicit vector(size_type n, value_type const& val = value_type(), allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
		this->assign(n, val);
	}

	/**
	 * Create a vector from a range of iterators
	 *
	 * @tparam InputIterator the type of iterator, must be at least an input iterator
	 * @param first the beginning of the iterator range
	 * @param last the end of the iterator range
	 * @param alloc allocator object, defaults to allocator_type
	 */
	template< class InputIterator >
	vector(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type()) :
		_alloc(alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
		this->assign(first, last);
	}

	/**
	 * Create a vector by deep-copying another
	 *
	 * @param x the vector to copy
	 */
	vector(vector const& x) :
		_alloc(x._alloc),
		_data(NULL),
		_size(0),
		_capacity(0)
	{
		this->assign(x.begin(), x.end());
	}

	/**
	 * Copy another vector into the current vector
	 *
	 * @param x the vector to copy
	 */
	vector& operator=(vector const& x)
	{
		if (&x != this)
			this->assign(x.begin(), x.end());
		return *this;
	}

	/**
	 * Destroy the current vector and its internal allocated buffer
	 */
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
		return this->begin() + this->size();
	}

	const_iterator end() const
	{
		return this->begin() + this->size();
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

	void resize(size_type n, value_type val = value_type())
	{
		const size_type size = this->size();

		this->reserve(n);
		if (n > size)
		{
			for (size_type i = size; i < n; ++i)
				this->_alloc.construct(this->_data + i, val);
		}
		else if (n < size)
		{
			for (size_type i = n; i < size; ++i)
				this->_alloc.destroy(this->_data + i);
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

	void reserve(size_type n)
	{
		pointer new_data;
		size_type new_capacity;

		if (n > this->max_size())
			throw std::length_error(__PRETTY_FUNCTION__);
		if (this->capacity() >= n)
			return;

		new_capacity = n;

		if (new_capacity < MIN_SIZE)
			new_capacity = MIN_SIZE;
		else if (this->capacity() > (new_capacity / 2))
			new_capacity = this->capacity() * 2;

		new_data = this->_alloc.allocate(new_capacity);

		for (size_type i = 0; i < this->size(); ++i)
		{
			this->_alloc.construct(new_data + i, this->_data[i]);
			this->_alloc.destroy(this->_data + i);
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

	reference at(size_type n)
	{
		if (n >= this->size())
			throw std::out_of_range(__PRETTY_FUNCTION__);
		return this->_data[n];
	}

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
	template< class InputIterator >
	void assign(InputIterator first, InputIterator last)
	{
		this->__dispatch_assign(first, last, ft::is_integral< InputIterator >());
	}

	void assign(size_type n, value_type const& val)
	{
		this->__assign_fill(n, val);
	}

	void push_back(value_type const& val)
	{
		size_type& size = this->_size;

		this->reserve(size + 1);
		this->get_allocator().construct(this->_data + size, val);
		++size;
	}

	void pop_back()
	{
		if (this->empty())
			return;
		--this->_size;
		this->get_allocator().destroy(this->_data + this->size());
	}

	iterator insert(iterator position, value_type const& val)
	{
		return this->__insert_fill(position, 1, val);
	}

	void insert(iterator position, size_type n, value_type const& val)
	{
		this->__insert_fill(position, n, val);
	}

	template< class InputIterator >
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		this->__dispatch_insert(position, first, last, ft::is_integral< InputIterator >());
	}

	iterator erase(iterator position)
	{
		return this->__erase(position - this->_data, 1);
	}

	iterator erase(iterator first, iterator last)
	{
		return this->__erase(first - this->_data, last - first);
	}

	// https://legacy.cplusplus.com/reference/vector/vector/swap/
	// allocator may or may not be swapped as the specification says nothing about it
	void swap(vector& x)
	{
		std::swap(this->_data, x._data);
		std::swap(this->_size, x._size);
		std::swap(this->_capacity, x._capacity);
	}

	void clear()
	{
		this->resize(0);
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
		if (n == 0)
			return position;

		const size_type offset = (position - this->begin());

		this->reserve(this->size() + n);

		iterator p = (this->begin() + offset);
		size_type i = (this->end() - p);

		while (i > 0)
		{
			--i;
			this->get_allocator().construct(p + n + i, p[i]);
			this->get_allocator().destroy(p + i);
		}
		return p;
	}

	iterator __move_left(iterator position, size_type n, size_type offset)
	{
		size_type i;

		if (n == 0 || offset == 0)
			return position;

		for (i = 0; i < offset; ++i)
		{
			this->get_allocator().construct(position + i, *(position + n + i));
			this->get_allocator().destroy(position + n + i);
		}

		return position - n;
	}

	iterator __insert_fill(iterator position, size_type n, value_type const& val)
	{
		iterator p;

		if (this->empty() || position == this->end())
		{
			const size_type start_size = this->size();

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

	// TODO fix performance issue when container is empty
	template< class InputIterator >
	void __insert_range(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag const)
	{
		iterator p = position;

		for (InputIterator it = first; it != last; ++it)
		{
			p = this->__insert_fill(p, 1, *it);
			++p;
		}
	}

	template< class ForwardIterator >
	void __insert_range(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag const)
	{
		typename ft::iterator_traits< ForwardIterator >::difference_type distance = 0;

		for (ForwardIterator it = first; it != last; ++it)
			++distance;

		this->__insert_range_distance(position, first, last, distance);
	}

	template< class RandomAccessIterator >
	void __insert_range(iterator position, RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag const)
	{
		typename ft::iterator_traits< RandomAccessIterator >::difference_type distance = (last - first);

		this->__insert_range_distance(position, first, last, distance);
	}

	template< class ForwardIterator >
	void __insert_range_distance(
	iterator position,
	ForwardIterator first,
	ForwardIterator last,
	typename ft::iterator_traits< ForwardIterator >::difference_type distance
	)
	{
		iterator p = this->__move_right(position, distance);

		for (ForwardIterator it = first; it != last; ++it)
			this->get_allocator().construct(p++, *it);
		this->_size += distance;
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
		this->__insert_range(position, first, last, typename ft::iterator_traits< InputIterator >::iterator_category());
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
		size_type i;

		for (i = 0; i < width; ++i)
			this->get_allocator().destroy(this->_data + index + i);
		this->__move_left(this->_data + index, width, elems - width - index);
		this->_size -= width;
		return this->_data + index;
	}
}; // class vector

/* ------------------------------------------------------------------------- */

template< class T, class Alloc >
bool operator==(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return (&lhs == &rhs) || (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class T, class Alloc >
bool operator!=(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator<=(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return !(rhs < lhs);
}

template< class T, class Alloc >
bool operator>(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return rhs < lhs;
}

template< class T, class Alloc >
bool operator>=(vector< T, Alloc > const& lhs, vector< T, Alloc > const& rhs)
{
	return !(lhs < rhs);
}

/* ------------------------------------------------------------------------- */

template< class T, class Alloc >
void swap(ft::vector< T, Alloc >& x, ft::vector< T, Alloc >& y)
{
	x.swap(y);
}

} // namespace ft

#endif // VECTOR_HPP
