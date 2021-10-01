#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>

namespace ft
{
	template<typename T>
	class my_iterator 
	{
	protected:
		typedef T* pointer_type;
		typedef ptrdiff_t difference_type;
		pointer_type ptr_type;
	

	public:
//**********************************************//
// Canon and constructors                       //
//**********************************************//
		my_iterator(void) : ptr_type(NULL) {};
		my_iterator(const my_iterator &src) {*this = src;};
		virtual ~my_iterator(void) {};
		my_iterator & operator=(my_iterator const & rhs) 
		{
			this->ptr_type = rhs.ptr_type;
			return *this;
		}

		my_iterator(pointer_type tpe): ptr_type(tpe) {};

//**********************************************//
// Logical comparison operators                 //
//**********************************************//
		bool operator<(const my_iterator &rhs) const {return ptr_type < rhs.ptr_type;};
		bool operator>(const my_iterator &rhs) const {return ptr_type > rhs.ptr_type;};
		bool operator<=(const my_iterator &rhs) const {return ptr_type <= rhs.ptr_type;};
		bool operator>=(const my_iterator &rhs) const {return ptr_type >= rhs.ptr_type;};
		bool operator==(const my_iterator &rhs) const {return ptr_type == rhs.ptr_type;};
		bool operator!=(const my_iterator &rhs) const {return ptr_type != rhs.ptr_type;};


	};










}

#endif