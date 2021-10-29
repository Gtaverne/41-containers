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

		typedef typename T::node Node;
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
		map_iterator(void) : ptr_iter(NULL), ptr_end(NULL) {}
		map_iterator(const map_iterator &src) : ptr_iter(src.ptr_iter), ptr_end(src.ptr_end), key_comp(src.key_comp) {}
		virtual ~map_iterator() {};
		map_iterator & operator=(map_iterator const & rhs) 
		{
			ptr_iter = rhs.ptr_iter;
			ptr_end = rhs.ptr_end;
			key_comp = rhs.key_comp;
			return *this;
		}

		map_iterator(Node* nd, Node* end): ptr_iter(nd), ptr_end(end) {};

		
		// operator map_iterator<const value_type>() const
		// {
		// 	std::cerr << "Map iterrator casting to const" << std::endl;
		// 	return this;
		// }

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
			if(ptr_iter->right != ptr_end)
			{
				ptr_iter = ptr_iter->right->min_nd();
				return *this;
			}
			else if (ptr_iter->parent)
			{
				std::cout << "Searching in parent node" << std::endl;
				key_type ref_key = ptr_iter->value.first;
				Node *tmp = ptr_iter->parent;
				while (tmp && this->key_comp(tmp->value.first, ref_key))
				{
					tmp = tmp->parent;
				}
				if (tmp)
				{
					ptr_iter = tmp;
					return *this;
				}
			}
			ptr_iter = ptr_end;
			return *this;
		}

		map_iterator &operator--(void)
		{
			if (ptr_iter == ptr_end)
			{
				ptr_iter = ptr_iter->parent;
				return *this;
			}
			else if (ptr_iter->left)
			{
				ptr_iter = ptr_iter->left->max_nd();
				return *this;
			}
			else if (ptr_iter->parent)
			{
				key_type ref_key = ptr_iter->value.first;
				Node *tmp = ptr_iter->parent;
				while(tmp && key_comp(ref_key, tmp->value.first))
					tmp = tmp->parent;
				if(tmp)
				{
					ptr_iter = tmp;
					return *this;
				}
			}
			else
			{
				ptr_iter = ptr_iter->min_nd();
			}
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
			--(*this);
			return (tmp);
		}

//**********************************************//
// Basic manips                                 //
//**********************************************//

		reference operator*(void) const	{return (ptr_iter->value);}
		pointer operator->(void) const {return ( &(operator*()));}

	};

//**********************************************//
// INSERT CONST_ITERATOR HERE                   //
//**********************************************//










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