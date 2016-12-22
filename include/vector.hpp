#ifndef __GUARD_VECTOR_HPP__
#define __GUARD_VECTOR_HPP__

#include <enumerable.hpp>
#include <vector>
#include <detail/generators.hpp>

template<typename T>
class Vector : public Enumerable<T, detail::Generator<Vector<T>>> {
	typedef EnumerableType Enumerable<T, detail::Generator<Vector<T>>>;
	constexpr Vector();

};

template<typename T>
constexpr Vector<T>::Vector() : EnumerableType(this) {
}

#endif
