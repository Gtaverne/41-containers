#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP


#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template<class Iter>
	class reverse_iterator 
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
		reverse_iterator(void) : _raw_iter() {};
		explicit reverse_iterator(iterator_type it): _raw_iter(it) {};
		template< class anyIter>
		reverse_iterator(const reverse_iterator<anyIter>& src): _raw_iter(src.base()) {};

		virtual ~reverse_iterator(void) {};
		reverse_iterator & operator=(reverse_iterator const & rhs) 
		{
			this->_raw_iter = rhs._raw_iter;
			return *this;
		}

		operator reverse_iterator<my_iterator<value_type const> >() const
		{
			return reverse_iterator<my_iterator<value_type const > > (_raw_iter);
		}

		operator reverse_iterator<my_iterator<value_type> >() 
		{
			return reverse_iterator<my_iterator<value_type> > (_raw_iter);
		}
	

//**********************************************//
// Basic + and -                                //
//**********************************************//
		reverse_iterator operator+(difference_type n) const
		{
			reverse_iterator tmp = *this;
			tmp += n; //+= permet deja de gerer le changement de signe
			return tmp;
		};
		difference_type operator-(const reverse_iterator &rhs) const
		{
			return rhs._raw_iter - _raw_iter;
		}
		reverse_iterator operator-(difference_type n) 
		{
			reverse_iterator tmp = *this;
			tmp -= n; //-= permet deja de gerer le changement de signe
			return tmp;
		};
		reverse_iterator &operator+=(difference_type n)
		{
			_raw_iter -= n;
			return *this;
		}
		reverse_iterator &operator-=(difference_type n)
		{
			_raw_iter += n;
			return *this;
		}
		friend reverse_iterator operator+(difference_type n, const reverse_iterator &rhs)
		{
			reverse_iterator tmp = rhs;
			tmp += n; //+= permet deja de gerer le changement de signe
			return tmp;
		}

//**********************************************//
// Incrementations                              //
//**********************************************//
		reverse_iterator& operator++(void)
		{
			--_raw_iter;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_raw_iter;
			return (tmp);
		}

		reverse_iterator& operator--(void)
		{
			++_raw_iter;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
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
	reverse_iterator<T> & operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &iter) {return (iter + n);};

	template <class T>
	reverse_iterator<T> & operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &iter) {return iter - n;};

	template <typename Iter1, typename Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() == rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) 
	{return lhs.base() != rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() > rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() < rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() >= rhs.base();};

	template <typename Iter1, typename Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() <= rhs.base();};
}


#endif