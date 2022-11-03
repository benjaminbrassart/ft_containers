/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:49:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/03 09:53:22 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

#include <algorithm>
#include <stdint.h>

#define TRUE_TYPE(Constant, Type)           \
 template<>                                 \
 struct Constant< Type > : public true_type \
 {                                          \
 }

namespace ft
{
template< class Iterator >
struct iterator_traits;

template< bool Cond, class T = void >
struct enable_if
{
};

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
	typedef ft::integral_constant< T, v > type;

	operator T()
	{
		return v;
	}
}; // struct integral_constant

typedef ft::integral_constant< bool, true > true_type;
typedef ft::integral_constant< bool, false > false_type;

template< class T >
struct is_integral : public ft::false_type
{
};

template< class T >
struct is_integral< T const > : public ft::is_integral< T >
{
};

TRUE_TYPE(is_integral, bool);
TRUE_TYPE(is_integral, char);
TRUE_TYPE(is_integral, wchar_t);
TRUE_TYPE(is_integral, signed char);
TRUE_TYPE(is_integral, short int);
TRUE_TYPE(is_integral, int);
TRUE_TYPE(is_integral, long int);
TRUE_TYPE(is_integral, unsigned char);
TRUE_TYPE(is_integral, unsigned short int);
TRUE_TYPE(is_integral, unsigned int);
TRUE_TYPE(is_integral, unsigned long int);

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
		std::swap(this->first, pr.first);
		std::swap(this->second, pr.second);
	}
}; // struct pair

template< class P1T1, class P1T2, class P2T1, class P2T2 >
bool operator==(ft::pair< P1T1, P1T2 > const& lhs, ft::pair< P2T1, P2T2 > const& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template< class P1T1, class P1T2, class P2T1, class P2T2 >
bool operator!=(ft::pair< P1T1, P1T2 > const& lhs, ft::pair< P2T1, P2T2 > const& rhs)
{
	return !(lhs == rhs);
}

template< class P1T1, class P1T2, class P2T1, class P2T2 >
bool operator<(ft::pair< P1T1, P1T2 > const& lhs, ft::pair< P2T1, P2T2 > const& rhs)
{
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template< class P1T1, class P1T2, class P2T1, class P2T2 >
bool operator<=(ft::pair< P1T1, P1T2 > const& lhs, ft::pair< P2T1, P2T2 > const& rhs)
{
	return !(rhs < lhs);
}

template< class P1T1, class P1T2, class P2T1, class P2T2 >
bool operator>(ft::pair< P1T1, P1T2 > const& lhs, ft::pair< P2T1, P2T2 > const& rhs)
{
	return rhs < lhs;
}

template< class P1T1, class P1T2, class P2T1, class P2T2 >
bool operator>=(ft::pair< P1T1, P1T2 > const& lhs, ft::pair< P2T1, P2T2 > const& rhs)
{
	return !(lhs < rhs);
}

template< class T1, class T2 >
pair< T1, T2 > make_pair(T1 x, T2 y)
{
	return pair< T1, T2 >(x, y);
}

template< class InputIterator1, class InputIterator2 >
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
		if (*first1 != *first2)
			return false;
		++first1;
		++first2;
	}
	return true;
}

template< class InputIterator1, class InputIterator2, class BinaryPredicate >
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1)
	{
		if (!pred(*first1, *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

template< class InputIterator1, class InputIterator2 >
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

template< class InputIterator1, class InputIterator2, class BinaryPredicate >
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
} // namespace ft

namespace std
{
template< class T1, class T2 >
void swap(ft::pair< T1, T2 >& x, ft::pair< T1, T2 >& y)
{
	x.swap(y);
}
} // namespace std
