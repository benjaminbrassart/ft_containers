/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:20:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/19 12:02:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <iostream>
#include <limits>
#include <utility>

template< class T >
struct enable_if_integral : public ft::enable_if< ft::is_integral< T >::value, T >
{
	using typename ft::enable_if< ft::is_integral< T >::value, T >::type;
};

template< class T >
struct enable_if_integer : public ft::enable_if< std::numeric_limits< T >::is_integer, T >
{
	using typename ft::enable_if< std::numeric_limits< T >::is_integer, T >::type;
};

int main()
{
	enable_if_integral< char >::type c(L'c');
	enable_if_integer< char >::type d(L'd');

	std::cout << "c: " << c << '\n' << "d: " << d << '\n';
}
