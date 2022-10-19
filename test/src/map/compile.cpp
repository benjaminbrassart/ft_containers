#include "map_test.hpp"

int main()
{
	std::cout << std::boolalpha;

	// map< char, char > m;
	// map< char, char >::iterator it;

	// m.insert(make_pair('c', 'c'));
	// m.insert(make_pair('c', 'A'));

	// it = m.find('c');

	// if (it != m.end())
	// {
	// 	std::cout << it->second << '\n';
	// 	it->second = 'Z';
	// 	std::cout << it->second << '\n';
	// }
	// else
	// 	std::cout << "not found";
	// std::cout << '\n';

	// print_map(m);

	// map< char, char > const m2;
	// map< char, char >::const_iterator it2;

	// it2 = m2.find('z');

	// if (it != m2.end())
	// 	std::cout << it->second;
	// else
	// 	std::cout << "not found";
	// std::cout << '\n';

	map< int, char > m3;

	m3.insert(make_pair('9', '9'));
	m3.insert(make_pair('8', '8'));
	m3.insert(make_pair('7', '7'));
	// m3.insert(make_pair('6', '6'));

	print_map(m3);
};
