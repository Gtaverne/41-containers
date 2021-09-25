#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>


namespace ft {
	template <class T, class Alloc = std::allocator<T> >

	class vector
	{
	public:
		typedef T		value_type;
		//see pointer_type and reference type
		typedef Alloc 	allocator_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef	allocator_type::pointer	pointer;	 //for the default allocator: value_type*
		typedef 	allocator_type::const_pointer	const_pointer; //for the default allocator: const value_type*
		typedef typename vector_iterator<vector<value_type> > iterator; //	a random access iterator to value_type	convertible to const_iterator
		typedef const_iterator	a random access iterator to const value_type	
		typedef reverse_iterator	reverse_iterator<iterator>	
		typedef const_reverse_iterator	reverse_iterator<const_iterator>	
		typedef difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
		typedef size_type




	private:
		T* _arr;
		int _capa_max;
		int _capa_current;
	};

};





#endif