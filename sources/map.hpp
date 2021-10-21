#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "map_iterator.hpp"

namespace ft
{

template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
class map
{

//**********************************************************//
// Variables                                                //
//**********************************************************//

public:
typedef Key key_type;
typedef T mapped_type;
typedef ft::pair<const Key, mapped_type> value_type;

private:
	typedef Tree<value_type, Compare, Alloc> tree;
	tree _tree;

public:

typedef Compare key_compare;
typedef typename tree::value_compare value_compare;
typedef Alloc allocator_type;

typedef typename tree::reference reference;
	// const_reference
	// pointer
	// const_pointer
	// iterator
	// const_iterator
	// reverse_iterator
	// const_reverse_iterator

	// difference_type
typedef size_t size_type;

//**********************************************************//
// Canon                                                    //
//**********************************************************//
explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc)
{
	// ft::Tree<ft::pair<int, int> > *proto;
	// for (int i = 0 ; i < 50; i++)
	// 	proto->insertValue(ft::make_pair(rand() % 20, rand() % 1000));
	// _tree(&proto);

	for (int i = 0 ; i < 50; i++)
		_tree.insertValue(ft::make_pair(rand() % 20, rand() % 1000));
}

//template <class InputIterator> map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

map (const map& x);

~map() {}

//**********************************************************//
// Iterator                                                 //
//**********************************************************//
//begin
// iterator begin();
// const_iterator begin() const;

//end
// iterator end();
// const_iterator end() const;

//rbegin
// reverse_iterator rbegin();
// const_reverse_iterator rbegin() const;

//rend
//  reverse_iterator rend();
// const_reverse_iterator rend() const;

//**********************************************************//
// Capacity                                                 //
//**********************************************************//
//empty
//bool empty() const;

//size
size_type size() const {return _tree.size();}

//max_size
size_type max_size() const {return _tree.max_size();}

//**********************************************************//
// Element access                                           //
//**********************************************************//
//[]
mapped_type& operator[] (const key_type& k) {return _tree[k];}


//**********************************************************//
// Modifiers                                                //
//**********************************************************//
//insert
// pair<iterator,bool> insert (const value_type& val);

//iterator insert (iterator position, const value_type& val);

//template <class InputIterator>
//void insert (InputIterator first, InputIterator last);


//erase
//void erase (iterator position);
//size_type erase (const key_type& k);
//void erase (iterator first, iterator last);

//swap
//void swap (map& x);

//clear
//void clear();


//**********************************************************//
// Observers                                                //
//**********************************************************//
//key comp
// key_compare key_comp() const;

//value_comp
//value_compare value_comp() const;


//**********************************************************//
// Operations                                               //
//**********************************************************//
//find
// iterator find (const key_type& k);
// const_iterator find (const key_type& k) const;

//count
//size_type count (const key_type& k) const;

//lower_bound
// iterator lower_bound (const key_type& k);
// const_iterator lower_bound (const key_type& k) const;

//upper bound
// iterator upper_bound (const key_type& k);
// const_iterator upper_bound (const key_type& k) const;

//equal range
//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
//pair<iterator,iterator>             equal_range (const key_type& k);


//**********************************************************//
// Get allocator                                            //
//**********************************************************//
//get_allocator
//allocator_type get_allocator() const;


};


}


#endif