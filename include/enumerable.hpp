#ifndef __GUARD_ENUMERABLE_HPP__
#define __GUARD_ENUMERABLE_HPP__

#include <enumerator.hpp>
#include <detail/generators.hpp>

/*
template<typename, typename>
struct Enumerator;
*/

template<typename ValueType, typename Generator>
struct Enumerable : Generator {
	
//	typedef Enumerator<ValueType, Generator> EnumeratorType;

	template<typename ...Args>
	constexpr Enumerable(Args...);

	template<typename Fun> 
	bool all(Fun);
	bool all();

//	EnumeratorType all();
	
	template<typename Functor>
	void each(Functor);
};

template<typename V, typename G>
template<class F>
void Enumerable<V, G>::each(F f) {
	G::each(f);
}

template<typename V, typename G>
template<typename ...Args>
constexpr Enumerable<V, G>::Enumerable(Args... args) : G(args...) {}

template<typename V, typename G>
template<typename F>
bool Enumerable<V, G>::all(F f) { 
	bool rv = true; 
	this->each([&rv, &f](const V& e) { return rv = (rv && f(e)); });
	return rv;
}

template<typename V, typename G>
bool Enumerable<V, G>::all() { 
	return all([](const V& v){ return (bool)v; });
}

#endif 
