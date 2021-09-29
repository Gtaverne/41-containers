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

	private:
		pointer _raw_data;
		allocator_type _alloc_type;
		size_type _max_capa;
		size_type _current_len;

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

// size
size_type size(void) const {return _current_len;};

// max_size
size_type max_size(void) const {return _alloc_type.max_size();};

// resize  Voici qui est absolument degueulasse
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
void reserve (size_type n);
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

//**********************************************//
// Element access                               //
//**********************************************//

// operator[]
    reference operator[] (size_type n) {return _raw_data[n];};
	const_reference operator[] (size_type n) const {return _raw_data[n];};
// at
// front
// back

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
// }

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
};





#endif