/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 05:12:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/20 01:56:46 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	}; // struct iterator

	template< class Iterator >
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	}; // struct iterator_traits

	template< class T >
	struct iterator_traits< T* >
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	}; // struct iterator_traits

	template< class T >
	struct iterator_traits< T const* >
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T const* pointer;
		typedef T const& reference;
		typedef random_access_iterator_tag iterator_category;
	}; // struct iterator_traits

	template< class Iterator >
	struct reverse_iterator : public iterator<
		typename iterator_traits< Iterator >::iterator_category,
		typename iterator_traits< Iterator >::value_type,
		typename iterator_traits< Iterator >::difference_type,
		typename iterator_traits< Iterator >::pointer,
		typename iterator_traits< Iterator >::reference
	>
	{
		public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits< Iterator >::iterator_category iterator_category;
		typedef typename iterator_traits< Iterator >::value_type value_type;
		typedef typename iterator_traits< Iterator >::difference_type difference_type;
		typedef typename iterator_traits< Iterator >::pointer pointer;
		typedef typename iterator_traits< Iterator >::reference reference;

		private:
		iterator_type base_iterator;

		public:
		reverse_iterator() :
			base_iterator()
		{
		}

		explicit reverse_iterator(iterator_type it) :
			base_iterator(it)
		{
		}

		template< class Iter >
		reverse_iterator(reverse_iterator< Iter > const& rev_it) :
			base_iterator(rev_it.base_iterator)
		{
		}

		iterator_type base() const
		{
			return this->base_iterator;
		}

		// TODO test implementation
		reference operator*() const
		{
			iterator_type it(this->base_iterator);

			return *--it;
		}

		// TODO test implementation
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->base_iterator - n);
		}

		// TODO test implementation
		reverse_iterator& operator++() // pre-increment => ++it
		{
			--this->base_iterator;
			return *this;
		}

		// TODO test implementation
		reverse_iterator operator++(int) // post-increment => it++
		{
			reverse_iterator it(*this);

			++*this;
			return it;
		}

		// TODO test implementation
		reverse_iterator& operator+=(difference_type n)
		{
			this->base_iterator -= n;
			return *this;
		}

		// TODO test implementation
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->base_iterator + n);
		}

		// TODO test implementation
		reverse_iterator& operator--() // pre-increment => --it
		{
			++this->base_iterator;
			return *this;
		}

		// TODO test implementation
		reverse_iterator operator--(int) // post-increment => it--
		{
			reverse_iterator it(*this);

			--*this;
			return it;
		}

		// TODO test implementation
		reverse_iterator& operator-=(difference_type n)
		{
			this->base_iterator += n;
			return *this;
		}

		// TODO test implementation
		pointer operator->() const
		{
			return &(this->operator*());
		}

		// TODO test implementation
		reference operator[](difference_type n) const
		{
			return this->base_iterator[-n - 1];
		}
	}; // struct reverse_iterator

	// TODO test implementation
	template< class Iterator >
	bool operator==(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	// TODO test implementation
	template< class Iterator >
	bool operator!=(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return !(lhs == rhs);
	}

	// TODO test implementation
	template< class Iterator >
	bool operator<(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return lhs.base() > rhs.base();
	}

	// TODO test implementation
	template< class Iterator >
	bool operator<=(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	// TODO test implementation
	template< class Iterator >
	bool operator>(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return lhs.base() < rhs.base();
	}

	// TODO test implementation
	template< class Iterator >
	bool operator>=(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	// TODO test implementation
	template< class Iterator >
	reverse_iterator< Iterator > operator+(typename reverse_iterator< Iterator >::difference_type n, reverse_iterator< Iterator > const& rev_it)
	{
		return rev_it + n;
	}

	// TODO test implementation
	template< class Iterator >
	typename reverse_iterator< Iterator >::difference_type operator-(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs)
	{
		return rhs.base() - lhs.base();
	}
} // namespace ft
