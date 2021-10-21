#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

//#include "tree.hpp"

#include <cstddef>
#include <iostream>
#include <iterator>

namespace ft
{
	template<class T>
	class map_iterator 
	{
	public:
		typedef T value_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		typedef typename T::key_compare key_comparator;
		typedef typename T::Node Node;
	
	private:
		Node *ptr_iter;
		Node *ptr_end;
		key_comparator key_comp;

	public:
		pointer getIter(void) const {return ptr_iter;};
//**********************************************//
// Canon, constructors and casting              //
//**********************************************//
		map_iterator(void) : ptr_iter(NULL), ptr_end(NULL) {};
		map_iterator(const map_iterator &src) {*this = src;};
		virtual ~map_iterator(void) {};
		map_iterator & operator=(map_iterator const & rhs) 
		{
			this->ptr_iter = rhs.ptr_iter;
			return *this;
		}

		map_iterator(Node begin, Node end): ptr_iter(begin), ptr_end(end) {};

		operator map_iterator<const value_type>() const
		{
			return map_iterator<value_type const>(ptr_iter);
		}

//**********************************************//
// Logical comparison operators                 //
//**********************************************//
		bool operator<(const map_iterator &rhs) const {return ptr_iter < rhs.ptr_iter;};
		bool operator>(const map_iterator &rhs) const {return ptr_iter > rhs.ptr_iter;};
		bool operator<=(const map_iterator &rhs) const {return ptr_iter <= rhs.ptr_iter;};
		bool operator>=(const map_iterator &rhs) const {return ptr_iter >= rhs.ptr_iter;};
		bool operator==(const map_iterator &rhs) const {return ptr_iter == rhs.ptr_iter;};
		bool operator!=(const map_iterator &rhs) const {return ptr_iter != rhs.ptr_iter;};


//**********************************************//
// Incrementations                              //
//**********************************************//
		map_iterator &operator++(void)
		{
			++ptr_iter;
			return *this;
		}

		map_iterator &operator--(void)
		{
			--ptr_iter;
			return *this;
		}

		map_iterator operator++(int)
		{
			map_iterator tmp(*this);
			++ptr_iter;
			return (tmp);
		}

		map_iterator operator--(int)
		{
			map_iterator tmp(*this);
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
	map_iterator<T> & operator+(typename map_iterator<T>::difference_type n, const map_iterator<T> &iter) {return iter + n;};

	template <class T>
	map_iterator<T> & operator-(typename map_iterator<T>::difference_type n, const map_iterator<T> &iter) {return iter - n;};

//**********************************************//
// Comparison tool   DEFINE EQUAL HERE          //
//**********************************************//

template <typename Iter1, typename Iter2>
bool operator==(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.getIter() == rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator!=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.getIter() != rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator<(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.getIter() < rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator>(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.getIter() > rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator<=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.getIter() <= rhs.getIter();};

template <typename Iter1, typename Iter2>
bool operator>=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.getIter() >= rhs.getIter();};
}

#endif