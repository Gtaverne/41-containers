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

//**********************************************//
// Member types                                 //
//**********************************************//
		typedef T		value_type;
		typedef Alloc 	allocator_type;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef	typename allocator_type::pointer	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		
		typedef my_iterator<value_type> iterator;
		typedef my_iterator<value_type const> const_iterator;
		typedef ft::reverse_iterator<iterator>	reverse_iterator;	
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;	
		
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

		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
		typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _raw_data(NULL), _alloc_type(alloc), _max_capa(0), _current_len(0)
		{assign(first, last);}

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
reverse_iterator rbegin(void) {return reverse_iterator(_raw_data + _current_len);};
const_reverse_iterator rbegin(void) const {return const_reverse_iterator(_raw_data + _current_len);};
// rend
reverse_iterator rend(void) {return reverse_iterator(_raw_data);};
const_reverse_iterator rend(void) const {return const_reverse_iterator(_raw_data);};


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

// assign
template <class InputIterator>
void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL)
{
	//size_type n = std::distance(first, last);
	size_type n = 0;
	InputIterator tmp = first;
	while (tmp++ != last)
		n++;

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
	if (_current_len > 0)
	{
		_alloc_type.destroy(&_raw_data[_current_len - 1]);
		_current_len--;
	}
}

// insert
iterator insert(iterator pos, const T& value )
{
	size_type l_start = &*pos - &*begin();
	insert(pos, 1, value);
	return (begin() + l_start);
}

void insert(iterator pos, size_type n, const T& value )
{
	size_type l_start = &*pos - &*begin();
	size_type l_end = &*end() - &*pos;

	if (_current_len + n > _max_capa)
		reserve(_current_len + n);
	for (size_type i = 0; i < l_end; i++)
		_alloc_type.construct(&_raw_data[_current_len - 1 + n - i], _raw_data[_current_len - 1 - i]);
	for (size_type i = 0; i < n; i++)
		_raw_data[l_start + i] = value;
	_current_len += n;
}

template< class InputIt >
void insert(iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = NULL)
{
	//size_type n = std::distance(first, last);
	size_type n = 0;
	InputIt tmp = first;
	while (tmp++ != last)
		n++;
	size_type l_start = &*pos - &*begin();
	size_type l_end = &*end() - &*pos;

	if (_current_len + n > _max_capa)
		reserve(_current_len + n);
	for (size_type i = 0; i < l_end; i++)
		_alloc_type.construct(&_raw_data[_current_len - 1 + n - i], _raw_data[_current_len - 1 - i]);

	while (first != last)
	{
		*((begin() + l_start++)) = *(first++);
	}
	_current_len += n;
}

// erase
iterator erase (iterator position) {return (erase(position, position +1));};

iterator erase(iterator first, iterator last)
{
	iterator res = first;
	iterator end = this->end();
	size_type i = &*last - &*first;

	while (last != end)
	{
		*first = *last;
		first++;
		last++;
	}
	while (i-- > 0)
		pop_back();
	return (res);
}

// swap
void swap(vector &rhs)
{
	pointer raw_data_tmp = rhs._raw_data;
	size_type capa_tmp = rhs._max_capa;
	size_type size_tmp = rhs._current_len;

	rhs._raw_data = this->_raw_data;
	rhs._max_capa = this->_max_capa;
	rhs._current_len = this->_current_len;

	this->_raw_data = raw_data_tmp;
	this->_max_capa = capa_tmp;
	this->_current_len = size_tmp;	
}

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
template< class T, class Alloc >
bool operator==(const vector<T, Alloc> &vec1, const vector<T, Alloc> &vec2)
{
	if (vec1.size() != vec2.size())
		return false;
	return (equal(vec1.begin(), vec1.end(), vec2.begin()));
}

template< class T, class Alloc >
bool operator!=(const vector<T, Alloc> &vec1, const vector<T, Alloc> &vec2)
{
	return (!(vec1 == vec2));
}

template< class T, class Alloc >
bool operator<(const vector<T, Alloc> &vec1, const vector<T, Alloc> &vec2)
{
	return (lexicographical_compare(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
}

template< class T, class Alloc >
bool operator<=(const vector<T, Alloc> &vec1, const vector<T, Alloc> &vec2)
{
	return (vec1 == vec2 || vec1 < vec2);
}

template< class T, class Alloc >
bool operator>(const vector<T, Alloc> &vec1, const vector<T, Alloc> &vec2)
{
	return (!(vec1 <= vec2));
}

template< class T, class Alloc >
bool operator>=(const vector<T, Alloc> &vec1, const vector<T, Alloc> &vec2)
{
	return (vec1 == vec2 || vec1 > vec2);
}

// swap
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
{x.swap(y);};

}

#endif