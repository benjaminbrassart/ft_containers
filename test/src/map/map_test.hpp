#pragma once

#include "../tester.hpp"

#include HEADER_MAP

// Here is another reason why c++98 sucks,
// you cannot use templates for typedefs
#define map NAMESPACE::map

template< class Key, class Value, class Compare, class Alloc >
void print_vector(map< Key, Value, Compare, Alloc > const& m)
{
	typename map< Key, Value, Compare, Alloc >::const_iterator it;
	typename map< Key, Value, Compare, Alloc >::const_reverse_iterator rit;

	std::cout
		<< "size: " << m.size() << '\n'
		<< "content:" << '\n';

	for (it = m.begin(); it != m.end(); ++it)
		std::cout << "  [" << it->first << "] = " << it->second << '\n';

	std::cout
		<< '\n'
		<< "content: (reverse):" << '\n';

	for (rit = m.rbegin(); rit != m.rend(); ++rit)
		std::cout << "  [" << rit->first << "] = " << it->second << '\n';
	std::cout << '\n';
}
