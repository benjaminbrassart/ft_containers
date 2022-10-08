#include "vector_test.hpp"

DESCRIBE({
	std::cout << std::boolalpha;

	vector<int> v;

	print_vector(v);
	std::cout << v.empty() << '\n';

	v.push_back(1);

	print_vector(v);
	std::cout << v.empty() << '\n';

	std::cout << std::noboolalpha;
});
