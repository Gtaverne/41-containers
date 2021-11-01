#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"
#include "pair.hpp"
#include "tree_iterator.hpp"
#include "reverse_iterator.hpp"

#define BLACK 0
#define RED 1


/*Let's not reinvent the wheel
https://www.programiz.com/dsa/red-black-tree

*/

namespace ft
{

template <class T>
struct Node
{
	typedef T value_type;
	bool color; //0 black, 1 red
	value_type val;
	Node *left;
	Node *right;
	Node *parent;

	Node(value_type const &val) : val(val) {} 
};


template <class T, class Compare, class Allocator = std::allocator<Node<T> > >
class Tree
{
public:
	typedef T value_type;
	typedef Compare key_comparator;
	
	typedef typename T::first_type key_type;
	typedef typename T::second_type mapped_type;
	typedef typename ft::Node<value_type> node;
	typedef node *node_ptr ;
	typedef Allocator allocator;
	typedef size_t size_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;

//for iterators
	std::ptrdiff_t difference_type;
	typedef ft::tree_iterator<node> iterator;
	typedef ft::tree_iterator<node> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


public:


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
		_branch_copy(*this, src._root, src.NIL);
	}

	~Tree()
	{
		_branch_clear();
		_alloc.destroy(NIL);
		_alloc.deallocate(NIL, 1);
	}


	Tree &operator=(Tree const src)
	{
		_branch_clear();
		_branch_copy(*this, src._root, src.NIL);
		return *this;
	}



//**********************************************************//
// Functions for map and iterators                          //
//**********************************************************//

void swap(Tree &rhs)
{
	allocator tempal = rhs._alloc;
	key_comparator tempcomp = rhs._comp;
	size_type tempsize = rhs._size;
	node_ptr tempnil = rhs.NIL;
	node_ptr temproot = rhs._root;

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

node_ptr end_node() {return NIL;}

node_ptr begin_node() {return min_nd(_root);}

size_type max_size() const {return _alloc.max_size();}

iterator iter_finder (value_type const &value)
{
	node_ptr found = value_finder(value);

	if (!found)
		return end();
	else
		return iterator(found, _root, NIL);
}



void clear()
{
	_branch_clear(_root);
	_root = NIL;
	_size = 0;
}

void erase(iterator it)
{
	_delete_node(it.node);
}

size_type keydeleter(const key_type& k)
{
	node_ptr found = value_finder(ft::make_pair(k, mapped_type()));
	if (found == NULL || found == NIL)
		return 0;
	_delete_node(found);
	return 1;
}

	node_ptr NIL;
private:
	node_ptr _root;
	key_comparator _comp;
	allocator _alloc; //to allocate nodes, it has the size of the 3 pointers + the bool + the val
	size_type _size;

/***********************************************************
** Tree Utils                                             **
** - New node, min, max, size                             **
** - Rotations                                            **
** - Insertion                                            **
** - Deletion                                             **
** - Finding                                              **
***********************************************************/

	node_ptr _new_node(value_type const &rawdata)
	{
		node_ptr node = _alloc.allocate(1);
		_alloc.construct(node, rawdata);
		node->color = RED;
		node->left = NIL;
		node->right = NIL;
		node->parent = NIL;

		return node;
	}

public:
	node_ptr min_nd(node_ptr nd) const
	{
		while (nd->left != NIL)
			nd = nd->left;
		return nd;
	}

	node_ptr max_nd(node_ptr nd) const
	{
		while (nd->right != NIL)
			nd = nd->right;
		return nd;
	}

	node_ptr getRoot() const
	{
		return _root;
	}

	size_type size() const
	{
		return _size;
	}

	void printTree(node_ptr node, int i = 0)
	{
		if (!node && i == 0 && _root)
			printTree(_root);
		else if (node != NIL)
		{
			std::cout << "Depth: " << i << " Key: " << node->val.first << " value: " << node->val.second << std::endl;
			if (node->left)
				printTree(node->left, i + 1);
			if (node->right)
				printTree(node->right, i + 1);
		}
	}


private:

/*
Left Rotation
     X                  Y
	/ \                / \
   a   Y       =>     X   c
      / \            / \  
	 b   c          a   b
*/


	void _left_rotate(node_ptr x)
	{
		node_ptr y = x->right;
		x->right = y->left;

		if (y->left != NIL)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL)
			_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

/*
Right Rotation
     X                  Y
	/ \                / \
   Y   c       =>     a   X
  / \                    / \  
 a	 b                  b   c
*/


	void _right_rotate(node_ptr x)
	{
		node_ptr y = x->left;
		x->left = y->right;

		if (y->right != NIL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL)
			_root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

public:
	void insertValue(value_type const &value)
	{
		node_ptr n = _new_node(value);

		ft::pair<node_ptr , bool> res = _insert_recursive(_root, n);
		
		if (res.second)
		{
			_size++;
			if (n->parent == NIL)
				n->color = BLACK;
			else
				_insert_fix(n);
			_root = n;
			while (_root->parent != NIL)
				_root = _root->parent;
		}
		else
		{
			_alloc.destroy(n);
			_alloc.deallocate(n, 1);
		}
	}

//Insert a pair in the tree
	ft::pair<node_ptr , bool> _insert_recursive(node_ptr rt, node_ptr n)
	{
		if (rt != NIL && _comp(n->val, rt->val))
		{
			if (rt->left != NIL)
				return _insert_recursive(rt->left, n);
			else
				rt->left = n;			
		}
		else if (rt != NIL && _comp(rt->val, n->val))
		{
			if (rt->right != NIL)
				return _insert_recursive(rt->right, n);
			else
				rt->right = n;
		}
		else if (rt != NIL)
			return ft::make_pair(rt, false);
		n->parent = rt;
		n->color = RED;
		n->left = NIL;
		n->right = NIL;
		return ft::make_pair(n, true);
	}

/*
Insert fixup
Feel free to check the detail of RBT algo to understand the next function
*/
	void _insert_fix (node_ptr nd)
	{
		node_ptr unc;

		while (nd->parent->color == RED)
		{
			if (nd->parent == nd->parent->parent->right)
			{
				unc = nd->parent->parent->left;
				if (unc->color == RED) //Red parent and red uncle
				{
					unc->color = BLACK;
					nd->parent->color = BLACK;
					nd->parent->parent->color = RED;
					nd = nd->parent->parent;
				}
				else
				{
					if (nd == nd->parent->left)
					{
						nd = nd->parent;
						_right_rotate(nd);
					}
					nd->parent->color = BLACK;
					nd->parent->parent->color = RED;
					_left_rotate(nd->parent->parent);
				}
			}
			else
			{
				unc = nd->parent->parent->right;
				if (unc->color == RED) //Red parent and red uncle
				{
					unc->color = BLACK;
					nd->parent->color = BLACK;
					nd->parent->parent->color = RED;
					nd = nd->parent->parent;
				}
				else
				{
					if (nd == nd->parent->right)
					{
						nd = nd->parent;
						_left_rotate(nd);
					}
					nd->parent->color = BLACK;
					nd->parent->parent->color = RED;
					_right_rotate(nd->parent->parent);
				}
			}
			if (nd == _root)
				break;
		}
		_root->color = BLACK;
	}	

	void _delete_node(node_ptr z)
	{
		node_ptr y = z;
		node_ptr x;
		bool y_original_color = y->color;
		if(z->left == NIL)
		{
			x = z->right;
			_transplant(z, z->right);
		}
		else if (z->right == NIL)
		{
			x = z->left;
			_transplant(z, z->left);
		}
		else
		{
			y = min_nd(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else
			{
				_transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			_transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		_alloc.destroy(z);
		_alloc.deallocate(z, 1);
		_size--;
		if (y_original_color == BLACK)
			_delete_fix(x);
	}

	void _delete_fix (node_ptr x)
		{
			node_ptr s;
			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_left_rotate(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							_right_rotate(s);
							s = x->parent->right;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						_left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_right_rotate(x->parent);
						s = x->parent->left;
					}
					if (s->right->color == BLACK && s->left->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							_left_rotate(s);
							s = x->parent->left;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						_right_rotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}

	node_ptr value_finder(const value_type &val) const
	{
		node_ptr current = _root;
		while (current != NIL)
		{
			if (_comp(val, current->val))
				current = current->left;
			else if (_comp(current->val, val))
				current = current->right;
			else
				return current;
		}
		return NULL;
	}

	void _transplant(node_ptr src, node_ptr dest)
	{
		if (src->parent == NIL)
			_root = dest;
		else if (src == src->parent->left)
			src->parent->left = dest;
		else
			src->parent->right = dest;
		dest->parent = src->parent;
		
	}

	void _branch_copy(Tree &dest, node_ptr src, node_ptr nil_src)
	{
		if (src != nil_src)
		{
			_branch_copy(dest, src->left, nil_src);
			dest.insertValue(src->val);
			_branch_copy(dest, src->right, nil_src);
		}
	}

	void _branch_clear(node_ptr  x = NULL)
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

//**********************************************************//
// Iterators                                                //
//**********************************************************//

	iterator begin(void) {return iterator(min_nd(_root), _root, NIL);}
	const_iterator begin(void) const {return iterator(min_nd(_root), _root, NIL);}
	iterator end(void) {return iterator(NIL, _root, NIL);}
	const_iterator end(void) const {return iterator(NIL, _root, NIL);}

	reverse_iterator rbegin(void)
	{
		iterator it = end();
		return reverse_iterator(it);
	}

	const_reverse_iterator rbegin(void) const
	{
		const_iterator it = end();
		return const_reverse_iterator(it);
	}

	reverse_iterator rend(void)
	{
		iterator it = begin();
		return reverse_iterator(it);
	}

	const_reverse_iterator rend(void) const 
	{
		const_iterator it = begin();
		return const_reverse_iterator(it);
	}





};
}



#endif
	