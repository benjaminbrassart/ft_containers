#include "./map_test.hpp"

int main()
{
	{
		map< int, int > m;

		for (int i = 0; i < 15; ++i)
			m[i] = i;
		m.erase(11);
		m.erase(10);
		m.erase(9);
		m.erase(13);
		m.erase(14);
		m.erase(8);
		print_map(m);
	}
}
