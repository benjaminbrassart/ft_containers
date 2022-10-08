#pragma once

#include "../tester.hpp"

#include HEADER_VECTOR

#define vector NAMESPACE::vector

template< class T, class Alloc >
void print_vector(vector< T, Alloc > const& vec)
{
	typename vector< T, Alloc >::const_iterator it;
	typename vector< T, Alloc >::const_reverse_iterator rit;

	std::cout
		<< "size: " << vec.size() << '\n'
		<< "content:" << '\n';

	for (it = vec.begin(); it != vec.end(); ++it)
		std::cout << "  [" << *it << "]" << '\n';

	std::cout
		<< '\n'
		<< "content: (reverse):" << '\n';

	for (rit = vec.rbegin(); rit != vec.rend(); ++rit)
		std::cout << "  [" << *rit << "]" << '\n';
	std::cout << '\n';
}
