/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 01:58:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/08/23 08:32:19 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "vector.hpp"
#include <iterator>
#include <iostream>
#include <vector>

using namespace ft;

static void _print(vector< int > const& v)
{
	std::cout
		<< "begin(): " << v.begin() << '\n'
		<< "end(): " << v.end() << '\n'
		<< "content: \n"
	;
	for (vector< int >::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << '\n';
	std::cout.flush();
}

int
main( void )
{
	std::boolalpha(std::cout);

	// int ints[5];

	// for (int i = 0; i < 5; ++i)
	// 	ints[i] = i;

	// reverse_iterator< int * > rbegin(&ints[5]);
	// reverse_iterator< int * > rend(&ints[0]);
	// reverse_iterator< int * > it = rbegin;

	// std::cout << (it - rend) << '\n';
	// for (it = rbegin; it != rend; ++it)
	// 	std::cout << *it << '\n';
	// std::cout << (it - rend) << '\n';
	// std::cout.flush();

	// vector< int > v;
	// vector< int > w;

	// for (int i = 0; i < 4; ++i)
	// 	v.push_back(i);

	// // w.push_back(-1);

	// _print(v);
	// std::cout << "------" << std::endl;
	// _print(w);

	// std::cout << "=============" << std::endl;

	// swap(v, w);

	// vector< int > z(w);

	// _print(v);
	// std::cout << "------" << std::endl;
	// _print(w);
	// std::cout << "------" << std::endl;
	// _print(z);
	// std::cout << "=============" << std::endl;
	// z.assign(w.begin(), w.end());
	// _print(z);
	// std::cout << "=============" << std::endl;
	// std::cout << (z == w) << std::endl;
	// std::cout << "=============" << std::endl;
	// z.pop_back();
	// std::cout << (z == w) << std::endl;

	vector< int > v;

	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(1);

	_print(v);

	return 0;
}
