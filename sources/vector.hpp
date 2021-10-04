#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"

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
		
		// ITERATORS, to test thoroughly
		typedef ft::my_iterator<value_type> iterator;
		typedef ft::my_iterator<value_type const> const_iterator;
		typedef ft::my_rev_iterator<value_type>	reverse_iterator;	
		typedef ft::my_rev_iterator<value_type const> const_reverse_iterator;	
		
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		pointer _raw_data;
		allocator_type _alloc_type;
		size_type _max_capa;
		size_type _current_len;


		//A private util function
		void grow_raw(size_type to_add)
		{
			if ( _current_len + to_add <= _max_capa)
				return ;
			if (_max_capa == 0)
				_max_capa = 1;
			while ( to_add + _current_len > _max_capa)
				_max_capa *= 2;
			pointer res = _alloc_type.allocate(_max_capa);
			for (size_type i = 0; i < _current_len; i++)
				res[i] = _raw_data[i];
			delete[] _raw_data;
			_raw_data = res;
		}

	public:
//**********************************************//
// Constructors and destructors                 //
//**********************************************//

		explicit vector (const allocator_type& alloc = allocator_type()): _raw_data(NULL), _alloc_type(alloc), _max_capa(0), _current_len(0)
		{}

		explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _raw_data(NULL), _alloc_type(alloc), _max_capa(0), _current_len(0)
		{
			reserve(n);
			_current_len = n;
			_max_capa = n;
			for (size_type i = 0; i < _current_len; i++)
			{
				_alloc_type.construct(&_raw_data[i], val);
			}
		}

		~vector()
		{
			this->clear();
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
iterator begin(void) {return iterator(_raw_data);};
const_iterator begin(void) const {return const_iterator(_raw_data);};
// end
iterator end(void) {return iterator(_raw_data + _current_len);};
const_iterator end(void) const {return const_iterator(_raw_data + _current_len);};

// rbegin
reverse_iterator rbegin(void) {return reverse_iterator(_raw_data);};
// rend
reverse_iterator rend(void) {return reverse_iterator(_raw_data + _current_len);};


//**********************************************//
// Capacity                                     //
//**********************************************//

// size
size_type size(void) const {return _current_len;};

// max_size
size_type max_size(void) const {return _alloc_type.max_size();};

// resize  ATTENTION, NE DONNE PAS LES BONS RESULTATS
void resize (size_type n, value_type val = value_type())
{
	//FONCTION A COMPLETER
	if (n > _max_capa)
	{
		size_type temp = _max_capa;
		grow_raw(n - _max_capa);
		for (size_type i = 0; i < n - temp; i++)
			push_back(val);
	}
}


// capacity
size_type capacity() const {return _max_capa;};

// empty
bool empty() const {return (_current_len == 0);};

// reserve
void reserve (size_type n)
{
	//FONCTION A COMPLETER
	if (n > _max_capa)
	{
		// size_type temp = _max_capa;
		grow_raw(n - _max_capa);
		// for (size_type i = 0; i < n - temp; i++)
		// 	push_back(val);
	}
}

//**********************************************//
// Element access                               //
//**********************************************//

// at
	reference at( size_type pos ) {return _raw_data[pos];};
	const_reference at( size_type pos ) const {return _raw_data[pos];};

// operator[]
    reference operator[] (size_type n) {return _raw_data[n];};
	const_reference operator[] (size_type n) const {return _raw_data[n];};
// front
	reference front(void) {return _raw_data[0];};
	const_reference front (void) const {return _raw_data[0];};
// back
	reference back(void) {return _raw_data[_current_len];};
	const_reference back (void) const {return _raw_data[_current_len];};

//**********************************************//
// Modifiers                                    //
//**********************************************//

// assign

// push_back
void push_back (const value_type &val)
{
	if (_max_capa == _current_len)
	{
		if (_current_len == 0)
			grow_raw(1);
		else
			grow_raw (2 * _current_len);
	}
	_raw_data[_current_len] = val;
	_current_len++;
}

// pop_back

// insert

// erase

// swap

// clear
void clear(void)
{
	// for (iterator it = begin(); i != end(); it++)
	// 	_raw_data.destroy(&(*it));
	_max_capa = 0;
}

//**********************************************//
// Allocator                                    //
//**********************************************//

// get_allocator






	};

//**********************************************//
// Non member functions overload                //
//**********************************************//

// relational operators
// swap
}


#endif