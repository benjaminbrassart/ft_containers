/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:20:26 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/17 17:31:58 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

template< class T >
struct enable_if_integral : public ft::enable_if< ft::is_integral< T >::value, T >
{
	using typename ft::enable_if< ft::is_integral< T >::value, T >::type;
};

int main()
{
	enable_if_integral< char >::type testInt;
}
