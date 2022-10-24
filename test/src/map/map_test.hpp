#pragma once

#include "../tester.hpp"

#include HEADER_MAP

template< class Key, class Value, class Compare, class Alloc >
void print_map(map< Key, Value, Compare, Alloc > const& m)
{
	typename map< Key, Value, Compare, Alloc >::const_iterator it;
	typename map< Key, Value, Compare, Alloc >::const_reverse_iterator rit;

	std::cout << "size: " << m.size() << '\n' << "content:" << '\n';

	for (it = m.begin(); it != m.end(); ++it)
		std::cout << "  [" << it->first << "] = " << it->second << '\n';

	std::cout << '\n' << "content: (reverse):" << '\n';

	for (rit = m.rbegin(); rit != m.rend(); rit++)
		std::cout << "  [" << rit->first << "] = " << rit->second << '\n';
	std::cout << '\n';
}
