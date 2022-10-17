/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:48:53 by bbrassar          #+#    #+#             */
/*   Updated: 2022/10/17 09:14:38 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <iostream>

#ifdef STD

# define HEADER_VECTOR <vector>
# define HEADER_MAP <map>
# define HEADER_STACK <stack>

# define NAMESPACE std

#else

# define HEADER_VECTOR "vector.hpp"
# define HEADER_MAP "map.hpp"
# define HEADER_STACK "stack.hpp"

# define NAMESPACE ft

#endif

using namespace NAMESPACE;

# ifndef SEED
#  define SEED 21U
# endif

#define DESCRIBE(Body) \
int main() { \
srand(SEED); \
std::cout << "Test: " << __FILE__ << '\n' << '\n'; \
Body; \
} \
