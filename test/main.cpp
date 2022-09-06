/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 01:58:21 by bbrassar          #+#    #+#             */
/*   Updated: 2022/09/06 05:08:31 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "vector.hpp"
#include <iterator>
#include <iostream>
#include <vector>

using namespace ft;

template< class T >
std::ostream& operator<<(std::ostream& os, vector< T > const& v)
{
	for (typename vector< T >::const_iterator it = v.begin(); it != v.end(); ++it)
		os << *it << '\n';
	return os;
}

// * cout << vector::begin() makes bad read, same for end, rbegin and rend
template< class T >
static void _print(vector< T > const& v)
{
	std::cout
		<< "size(): "
		<< v.size()
		<< '\n'

		<< "capacity(): "
		<< v.capacity()
		<< '\n'

		<< "content: \n"
		<< v

		<< std::flush;
}

int
main(void)
{
	std::cout << std::boolalpha;



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

	// -------------------------------------------------------------

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

	// -------------------------------------------------------------

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

	// -------------------------------------------------------------

	// vector< int > v;

	// v.push_back(4);
	// v.push_back(5);
	// v.push_back(6);
	// v.push_back(1);

	// _print(v);

	// std::cout << v.at(0) << '\n';
	// std::cout << v.at(4) << '\n';

	// -------------------------------------------------------------

	vector< char, std::allocator< char > > v;

	v.begin();

	for (int i = 0; i < 6; ++i)
	{
		v.push_back('0' + i);
	}

	_print(v);

	v.insert(v.begin(), 4, 'a');

	_print(v);

	return 0;
}
