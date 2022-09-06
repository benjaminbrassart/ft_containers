/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:49:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/09/06 09:07:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

#include <stdint.h>
#include <typeinfo>

namespace ft
{
	template< class Iterator >
	struct iterator_traits;

	struct random_access_iterator_tag;

	template< class T >
	struct is_random_access_iterator;

	template< bool Cond, class T = void >
	struct enable_if {};

	template< class T >
	struct enable_if< true, T >
	{
		typedef T type;
	}; // struct enable_if

	template< class T, T v >
	struct integral_constant
	{
		static T const value = v;
		typedef T value_type;
		typedef integral_constant< T, v > type;
		operator T() { return v; }
	}; // struct integral_constant

	typedef integral_constant< bool, true > true_type;
	typedef integral_constant< bool, false > false_type;

	template< class T >
	struct is_integral : public false_type {};

	template< >
	struct is_integral< bool > : public true_type {};

	template< >
	struct is_integral< char > : public true_type {};

	template< >
	struct is_integral< wchar_t > : public true_type {};

	template< >
	struct is_integral< signed char > : public true_type {};

	template< >
	struct is_integral< short int > : public true_type {};

	template< >
	struct is_integral< int > : public true_type {};

	template< >
	struct is_integral< long int > : public true_type {};

	template< >
	struct is_integral< long long int > : public true_type {};

	template< >
	struct is_integral< unsigned char > : public true_type {};

	template< >
	struct is_integral< unsigned short int > : public true_type {};

	template< >
	struct is_integral< unsigned int > : public true_type {};

	template< >
	struct is_integral< unsigned long int > : public true_type {};

	template< >
	struct is_integral< unsigned long long int > : public true_type {};

	template< class T1, class T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() :
			first(),
			second()
		{
		}

		template< class U, class V >
		pair(pair< U, V > const& pr) :
			first(pr.first),
			second(pr.second)
		{
		}

		pair(first_type const& a, second_type const& b) :
			first(a),
			second(b)
		{
		}

		void swap(pair& pr)
		{
			first_type a = pr.first;
			second_type b = pr.second;

			pr.first = this->first;
			pr.second = this->second;
			this->first = a;
			this->second = b;
		}
	}; // struct pair

	template< class T1, class T2>
	bool operator==(pair< T1, T2 > const& lhs, pair< T1, T2 > const& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2>
	bool operator!=(pair< T1, T2 > const& lhs, pair< T1, T2 > const& rhs)
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2>
	bool operator<(pair< T1, T2 > const& lhs, pair< T1, T2 > const& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2>
	bool operator<=(pair< T1, T2 > const& lhs, pair< T1, T2 > const& rhs)
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2>
	bool operator>(pair< T1, T2 > const& lhs, pair< T1, T2 > const& rhs)
	{
		return rhs < lhs;
	}

	template< class T1, class T2>
	bool operator>=(pair< T1, T2 > const& lhs, pair< T1, T2 > const& rhs)
	{
		return !(lhs < rhs);
	}

	template< class T1, class T2>
	void swap(pair< T1, T2 >& x, pair< T1, T2 >& y)
	{
		x.swap(y);
	}

	template< class T1, class T2>
	pair< T1, T2 > make_pair(T1 x, T2 y)
	{
		return pair< T1, T2 >(x, y);
	}

	template<
		class InputIterator1,
		class InputIterator2
	>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if(*first1 != *first2)
				return false;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template<
		class InputIterator1,
		class InputIterator2,
		class BinaryPredicate
	>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template<
		class InputIterator1,
		class InputIterator2
	>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template<
		class InputIterator1,
		class InputIterator2,
		class BinaryPredicate
	>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || pred(*first2, *first1))
				return false;
			else if (pred(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template< class InputIterator >
	typename ft::iterator_traits< InputIterator >::difference_type distance(InputIterator first, InputIterator last)
	{
		if (is_random_access_iterator< typename ft::iterator_traits< InputIterator >::iterator_category >::value)
			return last - first;

		typename ft::iterator_traits< InputIterator >::difference_type n = 0;
		InputIterator it = first;

		while (it != last)
		{
			++it;
			++n;
		}
		return n;
	}
} // namespace ft
