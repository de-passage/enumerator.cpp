#ifndef __GUARD_DETAIL_GENERATORS_HPP_
#define __GUARD_DETAIL_GENERATORS_HPP_

#include <defines.hpp>

namespace detail {

	template<class T>
		struct Generator {
			constexpr Generator(T*);

			template<typename F>
				void each(F);

			private: 
			T* _ptr;

		};
	template<class T>
		constexpr Generator<T>::Generator(T* p) : _ptr(p) { } 

	template<class T>
		template<typename F>
		void Generator<T>::each(F f) { 
			_ptr->each(f);
		}


	template<class T, int I>
		struct Generator<T(*&)[I]> {
			constexpr Generator(T (*&)[I]);

			template<typename F>
				void each(F); 

			private:
			T (*_arr)[I];
		};

	template<class T, int I>
		constexpr Generator<T(*&)[I]>::Generator(T (*&array)[I]) : _arr(array) {}

	template<class T, int I>
		template<typename F>
		void Generator<T(*&)[I]>::each(F f) {
			for(int i = 0; i < I; ++i)
				f((*_arr)[i]);
		}
}

#endif

