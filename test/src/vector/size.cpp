#include "vector_test.hpp"

int main()
{
	vector< int > v;

	std::cout << v.size() << '\n';

	v.push_back(1);

	std::cout << v.size() << '\n';

	v.assign(20, 50);

	std::cout << v.size() << '\n';

	v.clear();

	std::cout << v.size() << '\n';
}
