/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:20:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/03 13:41:18 by bbrassar         ###   ########.fr       */
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
	enable_if_integral< wchar_t >::type c(L'c');
	enable_if_integer< wchar_t >::type d(L'd');
	enable_if_integral< wchar_t const >::type cc(L'c');
	enable_if_integer< wchar_t const >::type dc(L'd');

	// enable_if_integral< char* >::type s(""); // <-- wont compile because pointer are not numeric types

	std::wcout << "c: " << c << '\n' << "d: " << d << '\n';
	std::wcout << "cc: " << cc << '\n' << "dc: " << dc << '\n';
}
