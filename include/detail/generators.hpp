#ifndef __GUARD_DETAIL_GENERATORS_HPP_
#define __GUARD_DETAIL_GENERATORS_HPP_

#include <defines.hpp>
#include <functional>

namespace detail {

	//////////////////////////////////////////////////////////////
	//
	// General purpose generator for classes providing a each() 
	// member function
	//
	//////////////////////////////////////////////////////////////
	template<class T>
		struct BasicGenerator {
			constexpr BasicGenerator(T*);

			template<typename F>
				void each(F);

			private: 
			T* _ptr;

		};
	template<class T>
		constexpr BasicGenerator<T>::BasicGenerator(T* p) : _ptr(p) { } 

	template<class T>
		template<typename F>
		void BasicGenerator<T>::each(F f) { 
			_ptr->each(f);
		}

	//////////////////////////////////////////////////////////////
	//
	// Type erased generator
	//
	//////////////////////////////////////////////////////////////

	template<typename V> 
		struct Holder {
			typedef const std::function<void(const V&)>& Functor;
			virtual void each(Functor) = 0;
			virtual ~Holder() = default;
		};


	template<typename T, typename V>
		class HolderImpl : public Holder<V> {
			public:
				typedef typename Holder<V>::Functor Functor;
				constexpr HolderImpl(T*);
				void each(Functor);
			private:
				T* _ptr;

		};

	template<typename T, typename V>
		constexpr HolderImpl<T, V>::HolderImpl(T* ptr) : _ptr(ptr) {
		}

	template<typename T, typename V>
		void HolderImpl<T, V>::each(Functor f) {
			_ptr->each(f);
		}

	template<typename V>
		class Generator {
			public: 
				template<class T>
					constexpr Generator(T*);

				template<typename F>
					void each(F);

				inline ~Generator() {
					delete _ptr; 
				}
			private:
				typedef typename Holder<V>::Functor Functor;
				Holder<V> *_ptr;

		};

	template<typename V>
		template<class T> 
		constexpr Generator<V>::Generator(T* t) : _ptr(new HolderImpl<T, V>(t)) {
		}


	template<typename V>
		template<typename F>
		void Generator<V>::each(F f) {
			_ptr->each(Functor(f));
		}


	//////////////////////////////////////////////////////////////
	//
	// Specialization for literal arrays
	//
	//////////////////////////////////////////////////////////////
	template<class T, int I>
		struct BasicGenerator<T(*&)[I]> {
			constexpr BasicGenerator(T (*&)[I]);

			template<typename F>
				void each(F); 

			private:
			T (*_arr)[I];
		};

	template<class T, int I>
		constexpr BasicGenerator<T(*&)[I]>::BasicGenerator(T (*&array)[I]) : _arr(array) {}

	template<class T, int I>
		template<typename F>
		void BasicGenerator<T(*&)[I]>::each(F f) {
			for(int i = 0; i < I; ++i)
				f((*_arr)[i]);
		}
}

#endif

