#include "vector_test.hpp"

DESCRIBE({
	vector<std::string> v;

	v.assign(100000000, "AAAAA");

	std::cout << v.size() << std::endl;

	v.clear();

	std::cout << v.size() << std::endl;

	vector<std::string> v2;

	std::cout << v.size() << std::endl;

	v2.assign(666, "ZZZZ");

	std::cout << v.size() << std::endl;

	v2.insert(v.begin() + 333, v.begin(), v.end());

	std::cout << v.size() << std::endl;
});
