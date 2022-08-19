/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 05:12:49 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/19 20:45:34 by bbrassar         ###   ########.fr       */
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
	struct reverse_iterator
	{
		typedef Iterator iterator_type;
		typedef typename iterator_traits< Iterator >::iterator_category iterator_category;
		typedef typename iterator_traits< Iterator >::value_type value_type;
		typedef typename iterator_traits< Iterator >::difference_type difference_type;
		typedef typename iterator_traits< Iterator >::pointer pointer;
		typedef typename iterator_traits< Iterator >::reference reference;

		reverse_iterator();

		explicit reverse_iterator(iterator_type it);

		template< class Iter >
		reverse_iterator(reverse_iterator< Iter > const& rev_it);

		iterator_type base() const;

		reference operator*() const;

		reverse_iterator operator+(difference_type n) const;

		reverse_iterator& operator++();
		reverse_iterator operator++(int);

		reverse_iterator& operator +=(difference_type n);

		reverse_iterator operator-(difference_type n) const;

		reverse_iterator& operator--();
		reverse_iterator operator--(int);

		reverse_iterator& operator -=(difference_type n);

		pointer operator->() const;
		reference operator[](difference_type n) const;
	}; // struct reverse_iterator

	template< class Iterator >
	bool operator==(reverse_iterator< Iterator >& lhs, reverse_iterator< Iterator >& rhs);

	template< class Iterator >
	bool operator!=(reverse_iterator< Iterator >& lhs, reverse_iterator< Iterator >& rhs);

	template< class Iterator >
	bool operator<(reverse_iterator< Iterator >& lhs, reverse_iterator< Iterator >& rhs);

	template< class Iterator >
	bool operator<=(reverse_iterator< Iterator >& lhs, reverse_iterator< Iterator >& rhs);

	template< class Iterator >
	bool operator>(reverse_iterator< Iterator >& lhs, reverse_iterator< Iterator >& rhs);

	template< class Iterator >
	bool operator>=(reverse_iterator< Iterator >& lhs, reverse_iterator< Iterator >& rhs);

	template< class Iterator >
	reverse_iterator< Iterator > operator+(typename reverse_iterator< Iterator >::difference_type n, reverse_iterator< Iterator > const& rev_it);

	template< class Iterator >
	typename reverse_iterator< Iterator >::difference_type operator-(reverse_iterator< Iterator > const& lhs, reverse_iterator< Iterator > const& rhs);
} // namespace ft
