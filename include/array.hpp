#ifndef __GUARD_ARRAY_HPP__
#define __GUARD_ARRAY_HPP__

#include <defines.hpp>
#include <enumerable.hpp>
#include <detail/generators.hpp>

template<typename T, SizeType Size>
class Array : public Enumerable<T> {
	public:
		typedef Enumerable<T> EnumerableType;

		constexpr Array();
		constexpr Array(T (&)[Size]); 
		constexpr Array(const Array<T, Size>&) = default;

		constexpr SizeType size() { return Size; }

		template<typename F>
		void each(F f); 

	private:
		T (&_arr)[Size];
};

template<typename T, SizeType Size>
constexpr Array<T, Size>::Array() : EnumerableType(this), _arr() {}

template<typename T, SizeType Size>
constexpr Array<T, Size>::Array(T (&arr)[Size]) : EnumerableType(this), _arr(arr) {}

template<typename T, SizeType Size>
template<typename F>
void Array<T, Size>::each(F f) { 
	for(SizeType i = 0; i < size(); ++i)
		f(_arr[i]);
}

#endif
