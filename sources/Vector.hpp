#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>


namespace ft {
	template <class T, class Alloc = std::allocator<T> >

	class vector
	{
	public:
		//check http://www.cplusplus.com/reference/vector/vector/?kw=vector
		typedef T		value_type;
		typedef Alloc 	allocator_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef	typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		
		// ON VERRA LES ITERATORS PLUS TARD
		// typedef typename vector_iterator<vector<value_type> > iterator;
		// typedef const_iterator;//	a random access iterator to const value_type	
		// typedef reverse_iterator	reverse_iterator<iterator>	
		// typedef const_reverse_iterator	reverse_iterator<const_iterator>	
		
		typedef difference_type
		typedef size_type size_t

		explicit vector (const allocator_type& alloc = allocator_type())): _raw(NULL), _max_capa(0), _current_capa(0)  {};

		~vector() {};
		
		vector & operator=(vector const & rhs)
		{
			//we must make a deep copy

			_capa_max = rhs._max_capa;
			_capa_current = rhs._current_capa;
		}



	private:
		value_type _raw;
		size_type _capa_max;
		size_type _capa_current;
	};

};





#endif