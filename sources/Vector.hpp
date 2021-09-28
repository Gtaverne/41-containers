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
		
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

//**********************************************//
// Constructors and destructors                 //
//**********************************************//

		explicit vector (const allocator_type& alloc = allocator_type()): _raw(NULL), _alloc_type(alloc), _max_len(0), _current_len(0)
		{}

		~vector()
		{
			// this->clear();
			_alloc_type.deallocate(_raw, _max_len);
		}
		
		vector & operator=(vector const & rhs)
		{
			if (this == &rhs)
				return *this;
			_max_len = rhs._max_len;
			_current_len = rhs._current_len;
			_alloc_type.deallocate(_raw, _max_len);
			//we must make a deep copy
			_raw = rhs._raw;
			return *this;
		}
//**********************************************//
// Iterators                                    //
//**********************************************//

// begin
// end
// rbegin
// rend

//**********************************************//
// Capacity                                     //
//**********************************************//

// size
// max_size
// resize
// capacity
// empty
// reserve

//**********************************************//
// Element access                               //
//**********************************************//

// operator[]
// at
// front
// back

//**********************************************//
// Modifiers                                    //
//**********************************************//

// assign
// push_back
// pop_back
// insert
// erase
// swap
// clear

//**********************************************//
// Allocator                                    //
//**********************************************//

// get_allocator




	private:
		value_type *_raw;
		allocator_type _alloc_type;
		size_type _max_len;
		size_type _current_len;
	};

//**********************************************//
// Non member functions overload                //
//**********************************************//

// relational operators
// swap

};





#endif