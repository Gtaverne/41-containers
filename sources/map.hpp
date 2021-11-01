#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

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
typedef ft::pair<const key_type, mapped_type> value_type;
typedef Compare key_compare;
typedef Alloc allocator_type;

class value_compare
{
public:
	value_compare() {}
	value_compare (value_compare const &src) {(void)src;}
	~value_compare() {}

	value_compare &operator=(const value_compare &) {return *this;}

	bool operator()(const value_type &a, const value_type &b) const
	{ return (key_compare()(a.first, b.first)); }
};

private:
	typedef typename ft::Tree<value_type, value_compare> mytree;
	typedef typename mytree::node Node;

public:
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	
	typedef typename mytree::iterator iterator;
	typedef typename mytree::const_iterator const_iterator;
	typedef typename mytree::reverse_iterator reverse_iterator;
	typedef typename mytree::const_reverse_iterator const_reverse_iterator;


	typedef size_t size_type;

//Rebinding, check this article http://www.cplusplus.com/reference/memory/allocator/
//typedef typename Alloc::template rebind<Node<value_type> >::other allocator_reb;


//**********************************************************//
// Canon                                                    //
//**********************************************************//
explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree()
{
	_alloc = alloc;
	_comp = comp;
	_value_comp = value_compare();
}

template <class InputIterator>
map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree()
{
	_alloc = alloc;
	_comp = comp;
	_value_comp = value_compare();
	insert(first, last);
}

map (const map& x) : _tree(x._tree), _alloc(x._alloc), _comp(x._comp), _value_comp(x._value_comp) {}

~map() {}

map &operator=(const map &rhs)
{
	_tree = rhs._tree;
	_alloc = rhs._alloc;
	return *this;
}


//**********************************************************//
// Iterator                                                 //
//**********************************************************//
//begin
iterator begin(){return (_tree.begin());}
const_iterator begin() const {return (_tree.begin());}

//end
iterator end() {return (_tree.end());}
const_iterator end() const {return (_tree.end());}

//rbegin
reverse_iterator rbegin() {return (_tree.rbegin());}
const_reverse_iterator rebegin() const {(_tree.rbegin());}

//rend
reverse_iterator rend() {return (_tree.rend());}
const_reverse_iterator rend() const {(_tree.rend());}

//**********************************************************//
// Capacity                                                 //
//**********************************************************//
//empty
bool empty() const { return (size() == 0); }

//size
size_type size() const {return _tree.size();}

//max_size
size_type max_size() const {return _tree.max_size();}

//**********************************************************//
// Element access                                           //
//**********************************************************//
//[]
mapped_type& operator[] (const key_type& k)
{
	value_type temp_val = ft::make_pair(k, mapped_type());
	iterator iter = _tree.iter_finder(temp_val);
	if (iter != end())
		return (iter.node->val.second);
	else
	{
		_tree.insertValue(temp_val);
		return (_tree.iter_finder(temp_val).node->val.second);
	}
	
}

//**********************************************************//
// Modifiers                                                //
//**********************************************************//
// //insert
pair<iterator,bool> insert (const value_type& val)
{
	size_type n = size();
	_tree.insertValue(val);
	pair<iterator, bool> res;
	res.first = find(val.first);
	res.second = (n != size());
	return res;
}

iterator insert (iterator position, const value_type& val)
{
	iterator previous(position);
	if (value_comp()(*previous, val) && value_comp()(val, *(++position)))
	{
		_tree.insertValue(val);
		return find(val.first);
	}
	return insert(val).first;
}

template <class InputIterator>
void insert (InputIterator first, InputIterator last)
{
	for(InputIterator it = first; it != last ; it++)
		_tree.insertValue(*it);
}


//erase
void erase (iterator position) {_tree.erase(position);}

size_type erase (const key_type& k)
{
	return _tree.keydeleter(k);
}

void erase (iterator first, iterator last)
{
	iterator tmp;
	while (first != last)
	{
		tmp = first;
		first++;
		erase(tmp);
	}
}

//swap
void swap (map& x)
{
	_tree.swap(x._tree);

	allocator_type tempal = _alloc;
	_alloc = x._alloc;
	x._alloc = tempal;
}

//clear
void clear() {_tree.clear();}


//**********************************************************//
// Observers                                                //
//**********************************************************//
//key comp
key_compare key_comp() const {return _comp;}

//value_comp
value_compare value_comp() const {return _value_comp;}


//**********************************************************//
// Operations                                               //
//**********************************************************//
//find
iterator find (const key_type& k)
{
	return (_tree.iter_finder(ft::make_pair(k, mapped_type())));
}
// const_iterator find (const key_type& k) const;

//count
size_type count (const key_type& k) const {return (_tree.find(k) ? 1 : 0);}

// //lower_bound
iterator lower_bound (const key_type& k)
{
	for (iterator tmp = begin(); tmp != end(); tmp++)
		if (!(key_comp()(tmp->first, k)))
			return tmp;
	return end();
}
// // const_iterator lower_bound (const key_type& k) const;

// //upper bound
iterator upper_bound (const key_type& k)
{
	for (iterator tmp = begin(); tmp != end(); tmp++)
		if ((key_comp()(k, tmp->first)))
			return tmp;
	return end();
}

// const_iterator upper_bound (const key_type& k) const;

//equal range
pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
pair<iterator,iterator>             equal_range (const key_type& k);


//**********************************************************//
// Get allocator                                            //
//**********************************************************//
//get_allocator
allocator_type get_allocator() const {return _alloc;}

private:
	mytree _tree;
	key_compare _comp;
	value_compare _value_comp;
	allocator_type _alloc;

};


}


#endif