#include "map_test.hpp"

typedef map<char, char> Map;
typedef Map::const_iterator ConstIterator;
typedef Map::iterator Iterator;

int main()
{
	std::cout << std::boolalpha;

	Map m;

	m.insert(make_pair('c', 'c'));
	m.insert(make_pair('c', 'A'));

	Iterator it = m.find('c');

	if (it != m.end())
	{
		std::cout << it->second << '\n';
		it->second = 'Z';
		std::cout << it->second << '\n';
	}
	else
		std::cout << "not found";
	std::cout << '\n';

	print_map(m);

	Map const m2;

	ConstIterator it2 = m2.find('z');

	if (it != m2.end())
		std::cout << it->second;
	else
		std::cout << "not found";
	std::cout << '\n';
};
