#include <iostream>
#include <enumerator.hpp>
#include <make_enumerator.hpp>
#include <detail/generators.hpp>
#include <array.hpp>
#include <vector.hpp>


template<typename T, int I, typename F>
auto each_in(T (&array)[I], F f) -> decltype(f(T()), void()) {
	for(int i = 0; i < I; ++i)
		f(array[i]);
}

class Functor {
	std::string _s;
	public:
	Functor(const std::string& str) : _s(str) {}
	void operator()(int i) {
			std::cout << _s << " : " << i + 10 << "!" << std::endl;
	}
};


int main() { 

	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	Array<int, 10> test(array);
	test.each([](int i) { std::cout << "test -> " << i << std::endl; } );
	std::cout << "All: " << test.all([](int i) { return i; }) << std::endl;

	return 0;
}
