/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:48:53 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/03 12:06:00 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#define SEPARATOR "==============================="

using std::cerr;
using std::cout;

namespace ft
{
template< class T >
std::string to_string(T const& obj)
{
	std::stringstream ss;

	ss << obj;
	return ss.str();
}

void separator(std::ostream& stream = std::cout)
{
	stream << "\n\n" << SEPARATOR << "\n\n\n";
}
} // namespace ft

#ifdef STD

#define HEADER_VECTOR <vector>
#define HEADER_MAP	  <map>
#define HEADER_STACK  <stack>

#define NAMESPACE std

#else

#define HEADER_VECTOR "vector.hpp"
#define HEADER_MAP	  "map.hpp"
#define HEADER_STACK  "stack.hpp"

#define NAMESPACE ft

#endif

#ifndef SEED
#define SEED 21U
#endif

#define DESCRIBE(Body)                         \
 int main()                                    \
 {                                             \
  srand(SEED);                                 \
  std::cout << "Test: " << __FILE__ << "\n\n"; \
  Body;                                        \
 }
