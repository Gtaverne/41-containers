#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#include <cstddef>
#include <iostream>

namespace ft
{
	template<typename T>
	class my_rev_iterator 
	{
	public:
		typedef T value_type;
		typedef value_type *pointer_type;
		typedef value_type &reference_type;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag my_iter_category;
	
	private:
		pointer_type ptr_iter;
	public:
		pointer_type getIter(void) const {return ptr_iter;};
//**********************************************//
// Canon, constructors and casting              //
//**********************************************//
		my_rev_iterator(void) : ptr_iter(NULL) {};
		my_rev_iterator(const my_rev_iterator &src) {*this = src;};
		virtual ~my_rev_iterator(void) {};
		my_rev_iterator & operator=(my_rev_iterator const & rhs) 
		{
			this->ptr_iter = rhs.ptr_iter;
			return *this;
		}

		my_rev_iterator(pointer_type tpe): ptr_iter(tpe) {};

		operator my_rev_iterator<const value_type>() const
		{
			return my_rev_iterator<value_type const>(ptr_iter);
		}

//**********************************************//
// Logical comparison operators                 //
//**********************************************//
		bool operator<(const my_rev_iterator &rhs) const {return ptr_iter < rhs.ptr_iter;};
		bool operator>(const my_rev_iterator &rhs) const {return ptr_iter > rhs.ptr_iter;};
		bool operator<=(const my_rev_iterator &rhs) const {return ptr_iter <= rhs.ptr_iter;};
		bool operator>=(const my_rev_iterator &rhs) const {return ptr_iter >= rhs.ptr_iter;};
		bool operator==(const my_rev_iterator &rhs) const {return ptr_iter == rhs.ptr_iter;};
		bool operator!=(const my_rev_iterator &rhs) const {return ptr_iter != rhs.ptr_iter;};

//**********************************************//
// Basic + and -                                //
//**********************************************//
		difference_type operator-(const my_rev_iterator &rhs) const {return ptr_iter - rhs.ptr_iter;};
		my_rev_iterator<T> operator+(difference_type n) const {return ptr_iter + n;};
		my_rev_iterator<T> operator-(difference_type n) const {return ptr_iter - n;};
		my_rev_iterator<T> &operator+=(difference_type n)
		{
			ptr_iter += n;
			return *this;
		}
		my_rev_iterator<T> &operator-=(difference_type n)
		{
			ptr_iter -= n;
			return *this;
		}
		friend my_rev_iterator<T> operator+(difference_type n, const my_rev_iterator &rhs)
		{
			return rhs.ptr_iter + n;
		}

//**********************************************//
// Incrementations                              //
//**********************************************//
		my_rev_iterator &operator++(void)
		{
			++ptr_iter;
			return *this;
		}

		my_rev_iterator &operator--(void)
		{
			--ptr_iter;
			return *this;
		}

		my_rev_iterator operator++(int)
		{
			my_rev_iterator tmp(*this);
			++ptr_iter;
			return (tmp);
		}

		my_rev_iterator operator--(int)
		{
			my_rev_iterator tmp(*this);
			--ptr_iter;
			return (tmp);
		}

//**********************************************//
// Basic manips                                 //
//**********************************************//

		reference_type operator*(void) const	{return (*ptr_iter);};
		pointer_type operator->(void) const {return (ptr_iter);};
		reference_type operator[](difference_type n) {return (ptr_iter[n]);};

	};

//**********************************************//
// Operator                                     //
//**********************************************//
	template <class T>
	my_rev_iterator<T> & operator+(typename my_rev_iterator<T>::difference_type n, const my_rev_iterator<T> &iter) {return iter + n;};

	template <class T>
	my_rev_iterator<T> & operator-(typename my_rev_iterator<T>::difference_type n, const my_rev_iterator<T> &iter) {return iter - n;};

//**********************************************//
// Comparison tool   DEFINE EQUAL HERE          //
//**********************************************//
}

template <typename Iter1, typename Iter2>
bool operator==(const ft::my_rev_iterator<Iter1>& lhs, const ft::my_rev_iterator<Iter2>& rhs) {return lhs.getIter() == rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator!=(const ft::my_rev_iterator<Iter1>& lhs, const ft::my_rev_iterator<Iter2>& rhs) {return lhs.getIter() != rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator<(const ft::my_rev_iterator<Iter1>& lhs, const ft::my_rev_iterator<Iter2>& rhs) {return lhs.getIter() < rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator>(const ft::my_rev_iterator<Iter1>& lhs, const ft::my_rev_iterator<Iter2>& rhs) {return lhs.getIter() > rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator<=(const ft::my_rev_iterator<Iter1>& lhs, const ft::my_rev_iterator<Iter2>& rhs) {return lhs.getIter() <= rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator>=(const ft::my_rev_iterator<Iter1>& lhs, const ft::my_rev_iterator<Iter2>& rhs) {return lhs.getIter() >= rhs.getIter();};

#endif