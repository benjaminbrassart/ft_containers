#include "./map_test.hpp"
#include <stdint.h>

/**
 * test goal: prove the map size changes according to the inserted and erased elements
 */
int main()
{
	map< int, std::string > m1;

	print_map(m1);

	ft::separator();

	for (int i = 0; i < 42; ++i)
	{
		m1.insert(NAMESPACE::make_pair(i, std::string(i, (i % 10) + '0')));
		print_map(m1);
	}

	ft::separator();

	for (int i = -42; i <= 42; ++i)
	{
		m1.erase(i);
		print_map(m1);
	}
}
