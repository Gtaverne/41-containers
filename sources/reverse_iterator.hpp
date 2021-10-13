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

//**********************************************//
// Canon, constructors and casting              //
//**********************************************//
		my_rev_iterator(void) : _raw_iter(NULL) {};
		explicit my_rev_iterator(iterator_type it): _raw_iter(it) {};
		my_rev_iterator(const my_rev_iterator<Iter>& src): _raw_iter(src._raw_iter) {};
		virtual ~my_rev_iterator(void) {};
		my_rev_iterator & operator=(my_rev_iterator const & rhs) 
		{
			this->_raw_iter = rhs._raw_iter;
			return *this;
		}


		operator my_rev_iterator<my_iterator<value_type const> >() const
		{
			return my_rev_iterator<my_iterator<value_type const > > (_raw_iter);
		}

		operator my_rev_iterator<my_iterator<value_type> >() 
		{
			return my_rev_iterator<my_iterator<value_type> > (_raw_iter);
		}
	

//**********************************************//
// Basic + and -                                //
//**********************************************//
		my_rev_iterator operator+(difference_type n) const
		{
			my_rev_iterator tmp = *this;
			tmp += n; //+= permet deja de gerer le changement de signe
			return tmp;
		};
		difference_type operator-(const my_rev_iterator &rhs) const
		{
			return _raw_iter - rhs._raw_iter;
		}
		my_rev_iterator operator-(difference_type n) 
		{
			my_rev_iterator tmp = *this;
			tmp -= n; //-= permet deja de gerer le changement de signe
			return tmp;
		};
		my_rev_iterator &operator+=(difference_type n)
		{
			_raw_iter -= n;
			return *this;
		}
		my_rev_iterator &operator-=(difference_type n)
		{
			_raw_iter += n;
			return *this;
		}
		friend my_rev_iterator operator+(difference_type n, const my_rev_iterator &rhs)
		{
			my_rev_iterator tmp = rhs;
			tmp += n; //+= permet deja de gerer le changement de signe
			return tmp;
		}

//**********************************************//
// Incrementations                              //
//**********************************************//
		my_rev_iterator &operator++(void)
		{
			--_raw_iter;
			return *this;
		}

		my_rev_iterator operator++(int)
		{
			my_rev_iterator tmp(*this);
			--_raw_iter;
			return (tmp);
		}

		my_rev_iterator &operator--(void)
		{
			++_raw_iter;
			return *this;
		}

		my_rev_iterator operator--(int)
		{
			my_rev_iterator tmp(*this);
			++_raw_iter;
			return (tmp);
		}

//**********************************************//
// Basic manips                                 //
//**********************************************//

		reference_type operator*(void) const
		{
			Iter tmp = _raw_iter;
			return (*(--tmp));
		}
		pointer_type operator->(void) const {return &(operator*());};
		reference_type operator[](difference_type n) const{return (*(_raw_iter - n - 1));};
		iterator_type base() const {return (_raw_iter);};

	};

//**********************************************//
// Operator                                     //
//**********************************************//
	template <class T>
	my_rev_iterator<T> & operator+(typename my_rev_iterator<T>::difference_type n, const my_rev_iterator<T> &iter) {return (iter + n);};

	template <class T>
	my_rev_iterator<T> & operator-(typename my_rev_iterator<T>::difference_type n, const my_rev_iterator<T> &iter) {return iter - n;};

	template <typename Iter1, typename Iter2>
	bool operator==(const my_rev_iterator<Iter1>& lhs, const my_rev_iterator<Iter2>& rhs) {return lhs.base() == rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator!=(const my_rev_iterator<Iter1>& lhs, const my_rev_iterator<Iter2>& rhs) {return lhs.base() != rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator<(const my_rev_iterator<Iter1>& lhs, const my_rev_iterator<Iter2>& rhs) {return lhs.base() < rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator>(const my_rev_iterator<Iter1>& lhs, const my_rev_iterator<Iter2>& rhs) {return lhs.base() > rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator<=(const my_rev_iterator<Iter1>& lhs, const my_rev_iterator<Iter2>& rhs) {return lhs.base() <= rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator>=(const my_rev_iterator<Iter1>& lhs, const my_rev_iterator<Iter2>& rhs) {return lhs.base() >= rhs.base();};
}


#endif