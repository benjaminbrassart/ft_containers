#include "./map_test.hpp"

struct Data
{
public:
	int _val;

	Data(int value = -42) :
		_val(value)
	{
	}

	Data(Data const& x) :
		_val(x._val)
	{
	}

	Data& operator=(Data const& x)
	{
		this->_val = x._val;
		return *this;
	}

	~Data()
	{
	}
};

std::ostream& operator<<(std::ostream& stream, Data const& data)
{
	stream << "Data { " << data._val << " }";
	return stream;
}

/**
 * test goal: prove the map permits access of data with bracket operator (operator[]),
 * and inserts default constructed data when the key is not found
 */
int main()
{
	{
		map< int, float > m;
	}

	ft::separator();

	{
		map< int, Data > m;

		for (int i = 0; i <= 42; ++i)
			m[42 + i] = i; // this is ok because constructor is not 'explicit'

		print_map(m);

		for (int i = -42; i <= 84; ++i)
			std::cout << m[i] << '\n';

		print_map(m);
	}
}
