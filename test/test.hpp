#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <memory>

namespace ftest 
{
	template <class T>
	class abitbol
	{
	public:
		typedef T value_type;


		typedef size_t size_type;

		abitbol(): _arr(0), _size(10) {};
		abitbol(abitbol const & src) 
		{
			*this = src;
		}
		
		abitbol & operator=(abitbol const & rhs)
		{
			this->_arr = rhs._arr;
			this->_size = rhs._size; 
		}
        virtual ~abitbol() {};

		abitbol(T n) : _arr(n), _size(n)
		{}

        abitbol & operator=(T const & rhs)
		{
			this->_arr = rhs;
			return *this;
		}

	//Getters and setters

	T getArr(void)
	{
		return this->_arr;
	}
	
	private:
		T _arr;
		int _size;
	};

//*************************************//
//   My vector class                   //
//*************************************//

	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;


		typedef size_t size_type;

		vector()
		{
			arr = new T[1];
			capacity = 1;
			current = 0;
		}

		void pushback (T data)
		{
			if (current == capacity)
			{
				T* temp = new T[2 * capacity];
				for (uint i = 0; i < capacity; i++)
				{
					temp[i] = arr[i];
				}
				delete[] arr;
				capacity *= 2;
				arr = temp;
			}
			arr[current] = data;
			current++;
		}

		~vector() {delete arr;};

		reference operator[](size_type n)
		{
			if (n > this->capacity)
				throw (std::out_of_range("Using [] operator with an index out of range"));
			return arr[n];	
		}
		
		private :
		T* arr;
		uint capacity;
		uint current;
	};
	
}

#endif