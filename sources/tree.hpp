#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"

#define BLACK 0
#define RED 1


/*Let's not reinvent the wheel
https://www.programiz.com/dsa/red-black-tree

*/

namespace ft
{

template <class T,class Compare = ft::less<typename T::first_type>, class Allocator = std::allocator<T> >
class Tree
{
public:
	typedef T value_type;
	typedef Compare key_comparator;
	
	typedef typename T::first_type key_type;
	typedef typename T::second_type mapped_type;
	typedef Allocator allocator;
	typedef size_t size_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;


public:
	struct Node
	{
		bool color; //0 black, 1 red
		value_type val;
		Node *left;
		Node *right;
		Node *parent;

		Node(value_type const &val) : val(val) {} 
	};

	Tree(const allocator alloc = allocator()) : _comp(key_comparator()), _size (0)
	{
		_alloc = alloc;

		//NIL is the last leaf everywhere, it's black
		NIL = _alloc.allocate(1);
		_alloc.construct(NIL, value_type());
		NIL->parent = NIL;
		NIL->left = NIL;
		NIL->right = NIL;
		NIL->color = BLACK;
		_root = NIL;
	}

	Tree(Tree const &src)
	{
		_alloc = src._alloc;
		_comp = src._comp;
		_size = src._size;
		NIL = _alloc.allocate(1);
		NIL->parent = NIL;
		NIL->left = NIL;
		NIL->right = NIL;
		NIL->color = BLACK;

		_root = NIL;
		//printree
		_branch_copy(*this, src.root, src.NIL);
	}

	~Tree()
	{
		_branch_clear();
		_alloc.destroy(NIL);
		_alloc.deallocate(NIL, 1);
	}






//**********************************************************//
// Functions for map and iterators                          //
//**********************************************************//

void swap(Tree &rhs)
{
	allocator tempal = rhs._alloc;
	key_comparator tempcomp = rhs._comp;
	size_type tempsize = rhs._size;
	Node *tempnil = rhs.NIL;
	Node *temproot = rhs._root;

	rhs._alloc = _alloc;
	_alloc = tempal;

	rhs._comp = _comp;
	_comp = tempcomp;

	rhs._size = _size;
	_size = tempsize;

	rhs.NIL = NIL;
	NIL = tempnil;

	rhs._root = _root;
	_root = temproot;
}



private:
	Node *_root;
	Node *NIL;
	key_comparator _comp;
	allocator _alloc; //to allocate nodes, it has the size of the 3 pointers + the bool + the val
	size_type _size;

//**********************************************************//
// Tree Utils                                               //
//**********************************************************//

Node *_new_node(value_type cont &rawdata)
{
	Node *node = _alloc.allocate(1);
	_alloc.construct(node, rawdata);
	node->color = RED;
	node->left = NIL;
	node->right = NIL;
	node->parent = NIL;

	return node;
}

Node *_papynode(Node const *node) const
{
	return node->parent->parent;
}

Node *_brothernode(Node const *node) const
{
	if (node == node->parent->left)
		return (node->parent->right);
	else
		return (node->parent>left);
}

Node *_unclenode(Node const *node) const
{
	
}


//**********************************************************//
// RBT algo functions                                       //
//**********************************************************//





	void _branch_copy(Tree &dest, Node *src, Node *nil_src)
	{
		if (src != nil_src)
		{
			_branch_copy(dest, src->left, nil_src);
			dest.insert(src->val);
			_branch_copy(dest, src->right, nil_src);
		}
	}
	

	void _branch_clear(Node * x = NULL)
	{
		if (x == NULL)
			x = _root;
		if (x != NIL)
		{
			_branch_clear(x->left);
			_branch_clear(x->right);
			_alloc.destroy(x);
			_alloc.deallocate(x, 1);
		}
	}

}
}



#endif
	