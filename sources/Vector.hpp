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

		explicit vector (const allocator_type& alloc = allocator_type()): _raw_data(NULL), _alloc_type(alloc), _max_capa(0), _current_len(0)
		{}

		~vector()
		{
			// this->clear();
			_alloc_type.deallocate(_raw_data, _max_capa);
		}
		
		vector & operator=(vector const & rhs)
		{
			if (this == &rhs)
				return *this;
			_max_capa = rhs._max_capa;
			_current_len = rhs._current_len;
			_alloc_type.deallocate(_raw_data, _max_capa);
			//we must make a deep copy
			_raw_data = rhs._raw_data;
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

size_type size(void) {return _current_len;};
// max_size
size_type max_size(void) {return _alloc_type.max_size();};
// resize  Voici qui est absolument degueulasse
// capacity
// empty
// reserve
void reserve (size_type n);
// {
// 	if (n > max_size())
// 		throw std::length_error("You are trying to reserve more than vector::max_size()");
// 	if (n > _max_capacity)
// 	{

// 	}
// }

//**********************************************//
// Element access                               //
//**********************************************//

// operator[]
    reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;
// at
// front
// back

//**********************************************//
// Modifiers                                    //
//**********************************************//

// assign

// push_back
// void push_back (const value_type &val)
// {
// 	if (_max_capa == 0)
// 	{
// 		//faire proprement la fonction d'allocation
// 		if (_current_len == 0)
// 			reserve(1);
// 		else
// 			reserve (2 * _current_len);
// 	}
	
// }

// pop_back

// insert

// erase

// swap

// clear
// void clear(void)
// {
// 	for (iterator it = begin(); i != end(); it++)
// 		_raw_data.destroy(&(*it));
// 	_max_capa = 0;
// }

//**********************************************//
// Allocator                                    //
//**********************************************//

// get_allocator




	private:
		value_type *_raw_data;
		allocator_type _alloc_type;
		size_type _max_capa;
		size_type _current_len;
	};

//**********************************************//
// Non member functions overload                //
//**********************************************//

// relational operators
// swap

};





#endif