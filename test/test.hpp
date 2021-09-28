#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

namespace ft 
{
	template <class T, class alloc = std::allocator<T> >
	class abitbol
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference

		abitbol(): arr(NULL), size(len) {};
        abitbol(abitbol const & src) 
		{
			*this = src;
		}
        abitbol & operator=(abitbol const & rhs)
		{
			this->arr = rhs.arr;
			this->size = rhs.size; 
		}
        virtual ~abitbol() {};

		abitbol(int n) : arr(NULL), size(len)
		{this->arr[0] = n;}

	private:
		T* arr;
		int size;
	};
	
}


#endif