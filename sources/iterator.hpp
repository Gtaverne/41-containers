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
		typedef T value_type;
		typedef value_type *pointer_type;
		typedef value_type &reference_type;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag my_iter_category;
	
	private:
		pointer_type ptr_iter;
	

	public:
//**********************************************//
// Canon and constructors                       //
//**********************************************//
		my_iterator(void) : ptr_iter(NULL) {};
		my_iterator(const my_iterator &src) {*this = src;};
		virtual ~my_iterator(void) {};
		my_iterator & operator=(my_iterator const & rhs) 
		{
			this->ptr_iter = rhs.ptr_iter;
			return *this;
		}

		my_iterator(pointer_type tpe): ptr_iter(tpe) {};

//**********************************************//
// Logical comparison operators                 //
//**********************************************//
		bool operator<(const my_iterator &rhs) const {return ptr_iter < rhs.ptr_iter;};
		bool operator>(const my_iterator &rhs) const {return ptr_iter > rhs.ptr_iter;};
		bool operator<=(const my_iterator &rhs) const {return ptr_iter <= rhs.ptr_iter;};
		bool operator>=(const my_iterator &rhs) const {return ptr_iter >= rhs.ptr_iter;};
		bool operator==(const my_iterator &rhs) const {return ptr_iter == rhs.ptr_iter;};
		bool operator!=(const my_iterator &rhs) const {return ptr_iter != rhs.ptr_iter;};

//**********************************************//
// Basic + and -                                //
//**********************************************//
		difference_type operator-(const my_iterator &rhs) const {return ptr_iter - rhs.ptr_iter;};
		my_iterator<T> operator+(difference_type n) const {return ptr_iter + n;};
		my_iterator<T> operator-(difference_type n) const {return ptr_iter - n;};
		my_iterator<T> &operator+=(difference_type n)
		{
			ptr_iter += n;
			return ptr_iter;
		}
		my_iterator<T> &operator-=(difference_type n)
		{
			ptr_iter -= n;
			return ptr_iter;
		}
		friend my_iterator<T> &operator+(difference_type n, const my_iterator &rhs) {return rhs.ptr_iter + n;};

//**********************************************//
// Incrementations                              //
//**********************************************//
		my_iterator &operator++(void)
		{
			++ptr_iter;
			return *this;
		}

		my_iterator &operator--(void)
		{
			--ptr_iter;
			return *this;
		}

		my_iterator operator++(int)
		{
			my_iterator tmp(*this);
			++ptr_iter;
			return (tmp);
		}

		my_iterator operator--(int)
		{
			my_iterator tmp(*this);
			--ptr_iter;
			return (tmp);
		}

//**********************************************//
// Basic manips                                 //
//**********************************************//

		reference_type operator*(void) const	{return (*ptr_iter);};
		pointer_type operator->(void) const {return (ptr_iter);};

	};










}

#endif