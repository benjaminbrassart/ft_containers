// #define STD
#include "./map_test.hpp"
#include <algorithm>
#include <functional>

/**
 * test goal: prove the map uses its compare object to sort the items
 */
int main()
{
	{
		cout << "std::greater\n\n";
		map< int, char, std::greater< int > > m;
		for (int i = 33; i < 127; ++i)
			m[i] = i;

		print_map(m, std::cout);
	}

	ft::separator();
}
