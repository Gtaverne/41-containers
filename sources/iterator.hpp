#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

namespace ft
{
	template<class T>
	class my_iterator 
	{
	public:
		typedef T value_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	
	private:
		pointer ptr_iter;
	public:
		pointer getIter(void) const {return ptr_iter;};
//**********************************************//
// Canon, constructors and casting              //
//**********************************************//
		my_iterator(void) : ptr_iter(NULL) {};
		my_iterator(const my_iterator &src) {*this = src;};
		virtual ~my_iterator(void) {};
		my_iterator & operator=(my_iterator const & rhs) 
		{
			this->ptr_iter = rhs.ptr_iter;
			return *this;
		}

		my_iterator(pointer tpe): ptr_iter(tpe) {};

		operator my_iterator<const value_type>() const
		{
			return my_iterator<value_type const>(ptr_iter);
		}

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
		difference_type operator-(const my_iterator &rhs) const {return ptr_iter - rhs.ptr_iter;}
		
		my_iterator<T> operator+(difference_type n) const {return ptr_iter + n;}
		my_iterator<T> operator-(difference_type n) const {return ptr_iter - n;}
		my_iterator<T> &operator+=(difference_type n)
		{
			ptr_iter += n;
			return *this;
		}
		my_iterator<T> &operator-=(difference_type n)
		{
			ptr_iter -= n;
			return *this;
		}
		friend my_iterator<T> operator+(difference_type n, const my_iterator &rhs)
		{
			return rhs.ptr_iter + n;
		}

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

		reference operator*(void) const	{return (*ptr_iter);};
		pointer operator->(void) const {return (ptr_iter);};
		reference operator[](difference_type n) {return (ptr_iter[n]);};

	};

//**********************************************//
// Operator in the case 'int +- iter'           //
//**********************************************//
	template <class T>
	my_iterator<T> & operator+(typename my_iterator<T>::difference_type n, const my_iterator<T> &iter) {return iter + n;};

	template <class T>
	my_iterator<T> & operator-(typename my_iterator<T>::difference_type n, const my_iterator<T> &iter) {return iter - n;};

//**********************************************//
// Comparison tool   DEFINE EQUAL HERE          //
//**********************************************//

template <typename Iter1, typename Iter2>
bool operator==(const my_iterator<Iter1>& lhs, const my_iterator<Iter2>& rhs) {return lhs.getIter() == rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator!=(const my_iterator<Iter1>& lhs, const my_iterator<Iter2>& rhs) {return lhs.getIter() != rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator<(const my_iterator<Iter1>& lhs, const my_iterator<Iter2>& rhs) {return lhs.getIter() < rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator>(const my_iterator<Iter1>& lhs, const my_iterator<Iter2>& rhs) {return lhs.getIter() > rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator<=(const my_iterator<Iter1>& lhs, const my_iterator<Iter2>& rhs) {return lhs.getIter() <= rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator>=(const my_iterator<Iter1>& lhs, const my_iterator<Iter2>& rhs) {return lhs.getIter() >= rhs.getIter();};
}

#endif