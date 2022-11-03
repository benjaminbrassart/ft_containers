#include "./map_test.hpp"

int main()
{
	{
		cout << "Increase\n\n";
		map< int, char > m;

		for (int i = 0; i < 2500000; ++i)
			m[i] = 0;
		cout << "size: " << m.size() << '\n';
		cout << "min : " << m.begin()->first << '\n';
		cout << "max : " << m.rbegin()->first << '\n';
	}

	ft::separator();

	{
		cout << "Decrease\n\n";
		map< int, char > m;

		for (int i = 2500000; i > 0; --i)
			m[i] = 0;
		cout << "size: " << m.size() << '\n';
		cout << "min : " << m.begin()->first << '\n';
		cout << "max : " << m.rbegin()->first << '\n';
	}
}
