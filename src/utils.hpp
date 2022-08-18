/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:49:15 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/18 03:18:27 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
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
		pair(pair< U, V > const &pr) :
			first(pr.first),
			second(pr.second)
		{
		}

		pair(first_type const &a, second_type const &b) :
			first(a),
			second(b)
		{
		}

		void swap(pair &pr)
		{
			first_type a = pr.first;
			second_type b = pr.second;

			pr.first = this->first;
			pr.second = this->second;
			this->first = a;
			this->second = b;
		}
	};

	template< class T1, class T2>
	bool operator==(pair< T1, T2 > const &lhs, pair< T1, T2 > const &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2>
	bool operator!=(pair< T1, T2 > const &lhs, pair< T1, T2 > const &rhs)
	{
		return !(lhs == rhs);
	}

	template< class T1, class T2>
	bool operator<(pair< T1, T2 > const &lhs, pair< T1, T2 > const &rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template< class T1, class T2>
	bool operator<=(pair< T1, T2 > const &lhs, pair< T1, T2 > const &rhs)
	{
		return !(rhs < lhs);
	}

	template< class T1, class T2>
	bool operator>(pair< T1, T2 > const &lhs, pair< T1, T2 > const &rhs)
	{
		return rhs < lhs;
	}

	template< class T1, class T2>
	bool operator>=(pair< T1, T2 > const &lhs, pair< T1, T2 > const &rhs)
	{
		return !(lhs < rhs);
	}

	template< class T1, class T2>
	void swap(pair< T1, T2 > &x, pair< T1, T2 > &y)
	{
		x.swap(y);
	}

	template< class T1, class T2>
	pair< T1, T2 > make_pair(T1 x, T2 y)
	{
		return pair< T1, T2 >(x, y);
	}
} // namespace ft
