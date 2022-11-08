#pragma once

#include "../tester.hpp"

#include HEADER_STACK

using NAMESPACE::stack;

template< class T, class Container >
void print_stack(stack< T, Container > const& s, std::ostream& stream = std::cout)
{
	stack< T, Container > c = s;

	stream << "size: " << c.size() << '\n' << "empty: " << c.empty() << '\n' << "content:" << '\n';

	while (!c.empty())
	{
		std::cout << " - " << c.top() << '\n';
		c.pop();
	}

	stream << '\n';
}
