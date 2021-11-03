#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
//http://www.cplusplus.com/reference/stack/stack/

	public:
		typedef Container container_type;
		typedef T value_type;
		typedef size_t size_type;

	protected:
		container_type c;
	
	public:
	//constructor
	explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {};

	//Destructor
	~stack () {};


//*************************************************************//
// Member functions                                            //
//*************************************************************//

	// empty
	bool empty(void) const {return c.empty();}
	// size
	size_type size(void) const {return c.size();}
	// top
	value_type& top(void) {return c.back();};
	const value_type& top(void) const {return c.back();}
	// push
	void push(const value_type &val) {c.push_back(val);}
	// pop
	void pop(void) {c.pop_back();}

//*************************************************************//
// Non member functions overload (we can use "friend")         //
//*************************************************************//
friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c == rhs.c);};

friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c != rhs.c);};

friend bool operator<  (const stack<T,Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c < rhs.c);};

friend bool operator<= (const stack<T,Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c <= rhs.c);};

friend bool operator>  (const stack<T,Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c > rhs.c);};

friend bool operator>= (const stack<T,Container>& lhs, const stack<T, Container>& rhs) {return (lhs.c >= rhs.c);};


};

}

#endif