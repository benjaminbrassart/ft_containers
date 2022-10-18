/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:20:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/18 13:27:42 by bbrassar         ###   ########.fr       */
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
	enable_if_integral< wchar_t const >::type c(L'é');
	enable_if_integer< wchar_t const >::type d(L'ë');

	std::cout << "c: " << c << '\n' << "d: " << d << '\n';
}
