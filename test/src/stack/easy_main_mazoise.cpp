#include "./stack_test.hpp"

#include <string>
#include <vector>

int main()
{
	stack< float > other_stack;
	std::vector< std::string > lst;

	lst.push_back("salut");
	lst.push_back("tu vas bien?");
	lst.push_back("super");
	lst.push_back("et toi?");

	stack< std::string, std::vector< std::string > > my_stack(lst);

	cout << std::boolalpha << other_stack.empty() << std::endl;
	other_stack.push(8.5); // 8.5;
	other_stack.push(42.4242); // 8.5; 42.4242;
	cout << other_stack.size() << '\n'; // 2
	other_stack.pop(); // 8.5;
	cout << other_stack.size() << '\n'; // 1
	other_stack.push(78541.987); // 8.5; 78541.987;
	cout << other_stack.size() << '\n'; // 2
	cout << other_stack.top() << '\n'; //78541.987
	cout << std::boolalpha << other_stack.empty() << std::endl;

	const std::string const_top = my_stack.top();

	cout << "const top: " << const_top << '\n';

	while (!my_stack.empty())
	{
		cout << my_stack.top() << '\n';
		my_stack.pop();
	}

	return (0);
}
