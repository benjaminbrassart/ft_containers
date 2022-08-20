/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 02:00:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/20 07:09:57 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

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
		public:
		typedef T value_type;
		typedef std::allocator< T > allocator_type; // TODO revert to Alloc
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef value_type* iterator;
		typedef value_type const* const_iterator;
		typedef ft::reverse_iterator< iterator > reverse_iterator;
		typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
		typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		private:
		allocator_type _alloc;
		pointer _data;
		size_type _size;
		size_type _capacity;

		public:
		// TODO test implementation
		explicit vector(allocator_type const& alloc = allocator_type()) :
			_alloc(alloc),
			_data(),
			_size(0),
			_capacity(0)
		{}

		// TODO test implementation
		explicit vector(size_type n, value_type const& val = value_type(), allocator_type const& alloc = allocator_type()) :
			_alloc(alloc),
			_data(),
			_size(0),
			_capacity(0)
		{
			this->assign(n, val);
		}

		// TODO test implementation
		template< class InputIterator >
		vector(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type()) :
			_alloc(alloc),
			_data(),
			_size(0),
			_capacity(0)
		{
			this->assign(first, last);
		}

		// TODO test implementation
		vector(vector const& x) :
			_alloc(x._alloc),
			_data(),
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

		public:
		// TODO test implementation
		iterator begin()
		{
			return this->_data;
		}

		// TODO test implementation
		const_iterator begin() const
		{
			return this->_data;
		}

		// TODO test implementation
		iterator end()
		{
			return this->_alloc.address(this->operator[](this->size()));
		}

		// TODO test implementation
		const_iterator end() const
		{
			return this->_alloc.address(this->_data[this->_size]);
		}

		// TODO test implementation
		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}

		// TODO test implementation
		const_reverse_iterator rbegin() const
		{
			return reverse_iterator(this->end());
		}

		// TODO test implementation
		reverse_iterator rend()
		{
			return reverse_iterator(this->begin());
		}

		// TODO test implementation
		const_reverse_iterator rend() const
		{
			return reverse_iterator(this->begin());
		}

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
			return this->_size == 0;
		}

		// TODO test implementation
		void reserve(size_type n)
		{
			if (this->capacity() >= n)
				return ;

			pointer new_data = this->_alloc.allocate(n * 2);

			for (size_type i = 0; i < this->size(); ++i)
			{
				this->_alloc.construct(this->_alloc.address(new_data[i]), this->_data[i]);
				this->_alloc.destroy(this->_alloc.address(this->_data[i]));
			}
			this->_alloc.deallocate(this->_data, this->capacity());
			this->_data = new_data;
			this->_capacity = n;
		}

		public:
		// TODO test implementation
		reference operator[](size_type n)
		{
			return this->_data[n];
		}

		// TODO test implementation
		const_reference operator[](size_type n) const
		{
			return this->_data[n];
		}

		// TODO test implementation
		reference at(size_type n)
		{
			if (n >= this->_size)
				throw std::out_of_range(__PRETTY_FUNCTION__);
			return this->_data[n];
		}

		// TODO test implementation
		const_reference at(size_type n) const
		{
			if (n >= this->_size)
				throw std::out_of_range(__PRETTY_FUNCTION__);
			return this->_data[n];
		}

		// TODO test implementation
		reference front()
		{
			return *(this->begin());
		}

		// TODO test implementation
		const_reference front() const
		{
			return *(this->begin());
		}

		// TODO test implementation
		reference back()
		{
			return *(this->rbegin());
		}

		// TODO test implementation
		const_reference back() const
		{
			return *(this->rbegin());
		}

		public:
		// TODO test implementation
		// TODO optimize with only 1 loop
		// BUG does not compile when value_type = int, use enable_if
		template< class InputIterator >
		void assign(InputIterator first, InputIterator last)
		{
			this->clear();
			this->insert(this->begin(), first, last);
		}

		// TODO test implementation
		// TODO optimize with only 1 loop
		// BUG does not compile when value_type = int, use enable_if
		void assign(size_type n, value_type const& val)
		{
			this->clear();
			this->resize(n, val);
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

		// TODO provide implementation
		iterator insert(iterator position, value_type const& val);

		// TODO provide implementation
		void insert(iterator position, size_type n, value_type const& val);

		// TODO provide implementation
		template< class InputIterator >
		void insert(iterator position, InputIterator first, InputIterator last);

		// TODO provide implementation
		iterator erase(iterator position);

		// TODO provide implementation
		iterator erase(iterator first, iterator last);

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

		public:
		allocator_type get_allocator() const
		{
			return this->_alloc;
		}
	}; // class vector

	// TODO provide implementation
	template< class T, class Alloc >
	bool operator==(vector< T, Alloc >& lhs, vector< T, Alloc >& rhs);

	// TODO provide implementation
	template< class T, class Alloc >
	bool operator!=(vector< T, Alloc >& lhs, vector< T, Alloc >& rhs);

	// TODO provide implementation
	template< class T, class Alloc >
	bool operator<(vector< T, Alloc >& lhs, vector< T, Alloc >& rhs);

	// TODO provide implementation
	template< class T, class Alloc >
	bool operator<=(vector< T, Alloc >& lhs, vector< T, Alloc >& rhs);

	// TODO provide implementation
	template< class T, class Alloc >
	bool operator>(vector< T, Alloc >& lhs, vector< T, Alloc >& rhs);

	// TODO provide implementation
	template< class T, class Alloc >
	bool operator>=(vector< T, Alloc >& lhs, vector< T, Alloc >& rhs);

	// TODO test implementation
	template< class T, class Alloc >
	void swap(vector< T, Alloc >& x, vector< T, Alloc >& y)
	{
		x.swap(y);
	}
} // namespace ft
