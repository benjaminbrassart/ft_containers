#pragma once

#include "../tester.hpp"

#include HEADER_MAP

using NAMESPACE::make_pair;
using NAMESPACE::map;
using NAMESPACE::pair;

template< class Key, class Value, class Compare, class Alloc >
void print_map(map< Key, Value, Compare, Alloc > const& m, std::ostream& stream = std::cout)
{
	typename map< Key, Value, Compare, Alloc >::const_iterator it;
	typename map< Key, Value, Compare, Alloc >::const_reverse_iterator rit;

	stream << "size: " << m.size() << '\n' << "content:" << '\n';

	for (it = m.begin(); it != m.end(); ++it)
		stream << "  [" << it->first << "] = " << it->second << '\n';

	stream << '\n' << "content: (reverse):" << '\n';

	for (rit = m.rbegin(); rit != m.rend(); rit++)
		stream << "  [" << rit->first << "] = " << rit->second << '\n';
	stream << '\n';
}
