/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 05:12:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/04 15:07:38 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

#include <cstddef>

namespace ft
{
	/* --------------------------------------------------------------------- */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* --------------------------------------------------------------------- */

	template< class T >
	struct is_input_iterator : public false_type {};

	template< >
	struct is_input_iterator< input_iterator_tag > : public true_type {};

	template< >
	struct is_input_iterator< forward_iterator_tag > : public true_type {};

	template< >
	struct is_input_iterator< bidirectional_iterator_tag > : public true_type {};

	template< >
	struct is_input_iterator< random_access_iterator_tag > : public true_type {};

	template< class T >
	struct is_input_iterator< T* > : public true_type {};

	template< class T >
	struct is_input_iterator< T const* > : public true_type {};

	/* --------------------------------------------------------------------- */

	template< class T >
	struct is_forward_iterator : public false_type {};

	template< >
	struct is_forward_iterator< forward_iterator_tag > : public true_type {};

	template< >
	struct is_forward_iterator< bidirectional_iterator_tag > : public true_type {};

	template< >
	struct is_forward_iterator< random_access_iterator_tag > : public true_type {};

	template< class T >
	struct is_forward_iterator< T* > : public true_type {};

	template< class T >
	struct is_forward_iterator< T const* > : public true_type {};

	/* --------------------------------------------------------------------- */

	template< class T >
	struct is_bidirectional_iterator : public false_type {};

	template< >
	struct is_bidirectional_iterator< bidirectional_iterator_tag > : public true_type {};

	template< >
	struct is_bidirectional_iterator< random_access_iterator_tag > : public true_type {};

	template< class T >
	struct is_bidirectional_iterator< T* > : public true_type {};

	template< class T >
	struct is_bidirectional_iterator< T const* > : public true_type {};

	/* --------------------------------------------------------------------- */

	template< class T >
	struct is_random_access_iterator : public false_type {};

	template< >
	struct is_random_access_iterator< random_access_iterator_tag > : public true_type {};

	template< class T >
	struct is_random_access_iterator< T* > : public true_type {};

	template< class T >
	struct is_random_access_iterator< T const* > : public true_type {};

	/* --------------------------------------------------------------------- */

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

	/* --------------------------------------------------------------------- */

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

	/* --------------------------------------------------------------------- */

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
		iterator_type _base;

		public:
		reverse_iterator() :
			_base()
		{
		}

		explicit reverse_iterator(iterator_type it) :
			_base(it)
		{
		}

		template< class Iter >
		reverse_iterator(reverse_iterator< Iter > const& rev_it) :
			_base(rev_it.base())
		{
		}

		iterator_type base() const
		{
			return this->_base;
		}

		// TODO test implementation
		reference operator*() const
		{
			iterator_type it(this->_base);

			return *--it;
		}

		// TODO test implementation
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->_base - n);
		}

		// TODO test implementation
		reverse_iterator& operator++() // pre-increment => ++it
		{
			--this->_base;
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
			this->_base -= n;
			return *this;
		}

		// TODO test implementation
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->_base + n);
		}

		// TODO test implementation
		reverse_iterator& operator--() // pre-increment => --it
		{
			++this->_base;
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
			this->_base += n;
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
			return this->_base[-n - 1];
		}
	}; // struct reverse_iterator

	// TODO test implementation
	template< class Iterator1, class Iterator2 >
	bool operator==(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	// TODO test implementation
	template< class Iterator1, class Iterator2 >
	bool operator!=(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
	{
		return lhs.base() != rhs.base();
	}

	// TODO test implementation
	template< class Iterator1, class Iterator2 >
	bool operator<(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
	{
		return lhs.base() > rhs.base();
	}

	// TODO test implementation
	template< class Iterator1, class Iterator2 >
	bool operator<=(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	// TODO test implementation
	template< class Iterator1, class Iterator2 >
	bool operator>(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
	{
		return lhs.base() < rhs.base();
	}

	// TODO test implementation
	template< class Iterator1, class Iterator2 >
	bool operator>=(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
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
	template< class Iterator1, class Iterator2 >
	typename reverse_iterator< Iterator1 >::difference_type operator-(reverse_iterator< Iterator1 > const& lhs, reverse_iterator< Iterator2 > const& rhs)
	{
		return rhs.base() - lhs.base();
	}
} // namespace ft
