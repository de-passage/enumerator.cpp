#include <iostream>
#include <enumerator.hpp>
#include <make_enumerator.hpp>
#include <detail/generators.hpp>
#include <array.hpp>
#include <vector.hpp>


void add_ten(int& i) {
	i += 10;
}

class Functor {
	std::string _s;
	public:
	Functor(const std::string& str) : _s(str) {}
	void operator()(int i) {
			std::cout << _s << " : " << (i += 10) << "!" << std::endl;
	}
};


int main() { 

	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	Array<int, 10> test(array);
	test.each([](int& i) { i += 100; } );
	test.each(add_ten);
	test.each(Functor("Test: "));
	test.each([](const int& i) { std::cout << "test -> " << i << std::endl; } );
	std::cout << "All: " << test.all([](int i) { return i != 111; }) << std::endl;

	return 0;
}
