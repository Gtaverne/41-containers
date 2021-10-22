#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

//#include "tree.hpp"

#include <cstddef>
#include <iostream>
#include <iterator>

namespace ft
{
	//https://www.cplusplus.com/reference/iterator/BidirectionalIterator/
	//Check here the possible operations

	template<class T>
	class map_iterator 
	{
	public:
		typedef T value_type;
		typedef typename T::pointer pointer;
		typedef typename T::reference reference;
		typedef std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		typedef typename T::Node Node;
		typedef typename T::key_type key_type;
		typedef typename T::key_comparator key_comparator;
	
	private:
		Node *ptr_iter;
		Node *ptr_end;
		key_comparator key_comp;

	public:
		Node *base(void) const {return ptr_iter;};
		Node *end(void) const {return ptr_end;};

//**********************************************//
// Canon, constructors and casting              //
//**********************************************//
		map_iterator(void) : ptr_iter(NULL), ptr_end(NULL) {};
		map_iterator(const map_iterator &src) {*this = src;};
		virtual ~map_iterator() {};
		map_iterator & operator=(map_iterator const & rhs) 
		{
			this->ptr_iter = rhs.ptr_iter;
			this->ptr_end = rhs.ptr_end;
			key_comp = rhs.key_comp;
			return *this;
		}

		map_iterator(Node* nd, Node* end): ptr_iter(nd), ptr_end(end) {};

		
		operator map_iterator<const value_type>() const
		{
			std::cerr << "Map iterrator casting " << std::endl;
			return map_iterator<const value_type>(ptr_iter, ptr_end);
		}

//**********************************************//
// Logical comparison operators                 //
//**********************************************//
		// bool operator==(const map_iterator &rhs) const {return ptr_iter == rhs.ptr_iter;}
		// bool operator!=(const map_iterator &rhs) const {return ptr_iter != rhs.ptr_iter;}


//**********************************************//
// Incrementations                              //
//**********************************************//
		map_iterator &operator++(void)
		{
			if(this->ptr_iter->right)
			{
				this->ptr_iter = this->ptr_iter->right->nd_Min();
				return *this;
			}
			else if (this->ptr_iter->parent)
			{
				//std::cout << "Searching in parent node" << std::endl;
				key_type ref_key = this->ptr_iter->value.first;
				Node *tmp = this->ptr_iter->parent;
				while (tmp && this->key_comp(tmp->value.first, ref_key))
					tmp = tmp->parent;
				if (tmp)
				{
					this->ptr_iter = tmp;
					return *this;
				}
			}
			this->ptr_iter = this->ptr_end;
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
			++(*this);
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

		reference operator*(void) const	{return (this->ptr_iter->value);}
		pointer operator->(void) const {return ( &(operator*()));}

	};

// //**********************************************//
// // Operator in the case 'int +- iter'           //
// //**********************************************//
// 	template <class T>
// 	map_iterator<T> & operator+(typename map_iterator<T>::difference_type n, const map_iterator<T> &iter) {return iter + n;};

// 	template <class T>
// 	map_iterator<T> & operator-(typename map_iterator<T>::difference_type n, const map_iterator<T> &iter) {return iter - n;};

//**********************************************//
// Comparison tool   DEFINE EQUAL HERE          //
//**********************************************//

template <typename Iter1, typename Iter2>
bool operator==(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return (lhs.base() == rhs.base() && lhs.end() == rhs.end());};

template <typename Iter1, typename Iter2>
bool operator!=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return (!(lhs == rhs));};

// template <typename Iter1, typename Iter2>
// bool operator<(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.base() < rhs.base();};

// template <typename Iter1, typename Iter2>
// bool operator>(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.base() > rhs.base();};

// template <typename Iter1, typename Iter2>
// bool operator<=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.base() <= rhs.base();};

// template <typename Iter1, typename Iter2>
// bool operator>=(const map_iterator<Iter1>& lhs, const map_iterator<Iter2>& rhs) {return lhs.base() >= rhs.base();};


}

#endif