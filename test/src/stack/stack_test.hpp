#pragma once

#include "../tester.hpp"

#include HEADER_STACK

using NAMESPACE::stack;

template< class T, class Container >
void print_map(stack< T, Container > const& s, std::ostream& stream = std::cout)
{
	stream << "size: " << s.size() << '\n' << "content:" << '\n';

	while (!s.empty())
	{
		std::cout << ' ' << s.top() << '\n';
		s.pop();
	}

	stream << '\n';
}
