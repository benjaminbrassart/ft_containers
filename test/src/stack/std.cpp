#include "./stack_test.hpp"
#include <deque>
#include <list>
#include <vector>

int main()
{
	{
		cout << "list\n";
		stack< int, std::list< int > > c;

		print_stack(c);
		c.push(4);
		print_stack(c);
		c.push(2);
		print_stack(c);
		c.pop();
		print_stack(c);
		c.pop();
		print_stack(c);
	}

	{
		cout << "deque\n";
		stack< int, std::deque< int > > c;

		print_stack(c);
		c.push(4);
		print_stack(c);
		c.push(2);
		print_stack(c);
		c.pop();
		print_stack(c);
		c.pop();
		print_stack(c);
	}

	{
		cout << "vector\n";
		stack< int, std::vector< int > > c;

		print_stack(c);
		c.push(4);
		print_stack(c);
		c.push(2);
		print_stack(c);
		c.pop();
		print_stack(c);
		c.pop();
		print_stack(c);
	}
}
