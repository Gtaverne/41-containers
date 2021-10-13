#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP


#include "iterator.hpp"
#include "iterator_utils.hpp"

namespace ft
{
	template<class Iter>
	class my_rev_iterator 
	{
	public:
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::pointer pointer_type;
		typedef typename iterator_traits<Iter>::reference reference_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::iterator_category iter_category;
		typedef Iter iterator_type;
	
	private:
		iterator_type _raw_iter;

	public:
		pointer_type getIter(void) const {return _raw_iter;};
		
//**********************************************//
// Canon, constructors and casting              //
//**********************************************//
		my_rev_iterator(void) : _raw_iter(NULL) {};
		my_rev_iterator(const my_rev_iterator &src) {*this = src;};
		virtual ~my_rev_iterator(void) {};
		my_rev_iterator & operator=(my_rev_iterator const & rhs) 
		{
			this->_raw_iter = rhs._raw_iter;
			return *this;
		}

		explicit my_rev_iterator(iterator_type it): _raw_iter(it) {};

		operator my_rev_iterator<my_iterator<value_type const> >() const
		{
			return my_rev_iterator<my_iterator<value_type const > > (_raw_iter);
		}

		operator my_rev_iterator<my_iterator<value_type> >() 
		{
			return my_rev_iterator<my_iterator<value_type> > (_raw_iter);
		}
	

//**********************************************//
// Logical comparison operators                 //
//**********************************************//
		bool operator<(const my_rev_iterator &rhs) const {return _raw_iter < rhs._raw_iter;};
		bool operator>(const my_rev_iterator &rhs) const {return _raw_iter > rhs._raw_iter;};
		bool operator<=(const my_rev_iterator &rhs) const {return _raw_iter <= rhs._raw_iter;};
		bool operator>=(const my_rev_iterator &rhs) const {return _raw_iter >= rhs._raw_iter;};
		bool operator==(const my_rev_iterator &rhs) const {return _raw_iter == rhs._raw_iter;};
		bool operator!=(const my_rev_iterator &rhs) const {return _raw_iter != rhs._raw_iter;};

//**********************************************//
// Basic + and -                                //
//**********************************************//
		difference_type operator-(const my_rev_iterator &rhs) const {return _raw_iter - rhs._raw_iter;};
		my_rev_iterator operator+(difference_type n) const
		{
			_raw_iter -= n;
			return *this;
		};
		my_rev_iterator operator-(difference_type n) const {return _raw_iter - n;};
		my_rev_iterator &operator+=(difference_type n)
		{
			_raw_iter += n;
			return *this;
		}
		my_rev_iterator &operator-=(difference_type n)
		{
			_raw_iter -= n;
			return *this;
		}
		friend my_rev_iterator operator+(difference_type n, const my_rev_iterator &rhs)
		{
			return rhs._raw_iter + n;
		}

//**********************************************//
// Incrementations                              //
//**********************************************//
		my_rev_iterator &operator++(void)
		{
			++_raw_iter;
			return *this;
		}

		my_rev_iterator &operator--(void)
		{
			--_raw_iter;
			return *this;
		}

		my_rev_iterator operator++(int)
		{
			my_rev_iterator tmp(*this);
			++_raw_iter;
			return (tmp);
		}

		my_rev_iterator operator--(int)
		{
			my_rev_iterator tmp(*this);
			--_raw_iter;
			return (tmp);
		}

//**********************************************//
// Basic manips                                 //
//**********************************************//

		reference_type operator*(void) const	{return (*_raw_iter);};
		pointer_type operator->(void) const {return (_raw_iter);};
		reference_type operator[](difference_type n) {return (_raw_iter[n]);};
		iterator_type base() const {return (_raw_iter);};

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