#ifndef __GUARD_ARRAY_HPP__
#define __GUARD_ARRAY_HPP__

#include <defines.hpp>
#include <enumerable.hpp>
#include <initializer_list>

template<typename T, SizeType Size>
class Array : public Enumerable<T, Array<T, Size> > {
	public:
		constexpr Array();
		constexpr Array(T (&)[Size]); 
		constexpr Array(const Array<T, Size>&);

		constexpr SizeType size() { return Size; }

		template<typename F>
		void each(F f); 

		typedef Enumerable<T, detail::Generator<T(*&)[Size]>> EnumerableType;
	private:
		T (&_arr)[Size];
};

template<typename T, int Size>
constexpr Array<T, Size>::Array() : EnumerableType(this), _arr() {}

template<typename T, int Size>
constexpr Array<T, Size>::Array(T (&arr)[Size]) : EnumerableType(this), _arr(arr) {}

template<typename T, int Size>
template<typename F>
void Array<T, Size>::each(F f) { 
	for(auto i = 0; i < size(); ++i)
		f(_arr[i]);
}

#endif
