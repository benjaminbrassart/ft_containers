/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:49:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/19 20:40:59 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

namespace ft
{
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
} // namespace ft
