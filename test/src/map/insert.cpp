#include "./map_test.hpp"
#include <deque>

int main()
{
	{
		std::deque< pair< long, double > > dq;
		map< long, double > m;

		print_map(m);

		for (long l = 555; l < 666; ++l)
			dq.push_front(make_pair(l, l * 6.9));

		print_map(m);

		for (int i = 0; i < 5; ++i)
			m.insert(dq.begin(), dq.end());

		print_map(m);
	}

	ft::separator();
}
