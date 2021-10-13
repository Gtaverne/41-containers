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
		typedef ft::my_rev_iterator<iterator>	reverse_iterator;	
		typedef ft::my_rev_iterator<iterator> const_reverse_iterator;	
		
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		pointer _raw_data;
		allocator_type _alloc_type;
		size_type _max_capa;
		size_type _current_len;


		//A private util function
		void _grow_raw(void) 
		{
			if (_max_capa == 0)
				reserve(1);
			else
				reserve(_max_capa * 2);
		}

		// void _grow_raw(size_type to_add) {reserve(_max_capa + to_add);};

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
				_alloc_type.construct(&_raw_data[i], val);
		}

		vector(const vector &rhs) : _raw_data(NULL), _alloc_type(rhs._alloc_type), _max_capa(rhs._max_capa), _current_len(rhs._current_len)
		{
			if (rhs._raw_data)
			{
				_raw_data = _alloc_type.allocate(_max_capa);
				for (size_type i = 0; i < _current_len; i++)
					_alloc_type.construct(&_raw_data[i], rhs._raw_data[i]);
			}
		}

		~vector()
		{
			clear();
			if (_raw_data)
				_alloc_type.deallocate(_raw_data, _max_capa);
		}
		
		vector & operator=(vector const & rhs)
		{
			if (this == &rhs)
				return *this;
			clear();
			if (_max_capa < rhs._current_len)
				reserve(rhs._current_len);
			_current_len = rhs._current_len;
			if (_raw_data)
				_alloc_type.deallocate(_raw_data, _max_capa);
			if (rhs._raw_data)
			{
				_raw_data = _alloc_type.allocate(_max_capa);
				for (size_type i = 0; i < _current_len; i++)
					_alloc_type.construct(&_raw_data[i], rhs._raw_data[i]);
			}
			else
				_raw_data = NULL;
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

// resize
void resize (size_type n, value_type val = value_type())
{
	if (n > _max_capa)
		reserve(n);
	if (n > _current_len)
	{
		for (size_type i = _current_len; i < n; i++)
			_alloc_type.construct(&_raw_data[i], val);
		_current_len = n;
	}
	else
	{
		for (size_type i = n; i < _current_len; i++)
			_alloc_type.destroy(&_raw_data[i]);
		_current_len = n;
	}
}


// capacity
size_type capacity() const {return _max_capa;};

// empty
bool empty() const {return (_current_len == 0);};

// reserve
void reserve (size_type n)
{
	if (n > max_size())
		throw std::length_error("n greater than vector::max_size()");
	if (n > _max_capa)
	{
		value_type *tmp = _alloc_type.allocate(n);

		for (size_type i = 0; i < _current_len; i++)
		{
			_alloc_type.construct(&tmp[i], _raw_data[i]);
			_alloc_type.destroy(&_raw_data[i]);
		}

		if (_raw_data)
			_alloc_type.deallocate(_raw_data, _max_capa);
		_max_capa = n;
		_raw_data = tmp;
	}
}

//**********************************************//
// Element access                               //
//**********************************************//

// at
	reference at( size_type pos )
	{
		if (pos >= _current_len)
			throw (std::out_of_range("out of range"));
		return _raw_data[pos];
	}
	const_reference at( size_type pos ) const
	{
		if (pos >= _current_len)
			throw (std::out_of_range("out of range"));
		return _raw_data[pos];
	}
// operator[]
    reference operator[] (size_type n) {return _raw_data[n];};
	const_reference operator[] (size_type n) const {return _raw_data[n];};
// front
	reference front(void) {return _raw_data[0];};
	const_reference front (void) const {return _raw_data[0];};
// back
	reference back(void) {return _raw_data[_current_len - 1];};
	const_reference back (void) const {return _raw_data[_current_len - 1];};

//**********************************************//
// Modifiers                                    //
//**********************************************//

// assign BIEN COMPRENDRE LE ENABLE IF
template <class InputIterator>
void assign (InputIterator first, InputIterator last)
{
	size_type n = std::distance(first, last);
	if (n > _max_capa)
		reserve(n);
	for (size_type i = 0; i < _current_len; i++)
		_alloc_type.destroy(&_raw_data[i]);
	for (size_type i = 0; i < n; i++)
		_alloc_type.construct(&_raw_data[i], *first++);
	_current_len = n;
}

void assign (size_type n, const value_type& val)
{
	if (n > _max_capa)
		reserve(n);
	for (size_type i = 0; i < _current_len; i++)
		_alloc_type.destroy(&_raw_data[i]);
	for (size_type i = 0; i < n; i++)
		_alloc_type.construct(&_raw_data[i], val);
	_current_len = n;
}

// push_back
void push_back (const value_type &val)
{
	if (_max_capa == _current_len)
		_grow_raw();
	_alloc_type.construct(&_raw_data[_current_len], val);
	_current_len++;
}

// pop_back
void pop_back(void)
{
	_alloc_type.destroy(&_raw_data[_current_len - 1]);
	_current_len--;
}

// insert
iterator insert(iterator pos, const T& value );

void insert(iterator pos, size_type count, const T& value );

template< class InputIt >
void insert(iterator pos, InputIt first, InputIt last );

// erase

// swap

// clear
void clear(void)
{
	while (_current_len > 0)
		pop_back();
}

//**********************************************//
// Allocator                                    //
//**********************************************//

// get_allocator
allocator_type get_allocator() const {return _alloc_type;}

	};

//**********************************************//
// Non member functions overload                //
//**********************************************//

// relational operators
// swap
}


#endif