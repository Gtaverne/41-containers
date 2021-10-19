#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"
#include "pair.hpp"

namespace ft
{

template <class T,class Compare = less<typename T::first_type>, class Alloc = std::allocator<T> >
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

/********************************
todo

CANON


insertValue
delete
deleteKey
[]
destroy
height

find

************************************/
	struct Node
	{
		value_type value;
		Node *left;
		Node *right;
		Node *parent;


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

	Tree (const key_comparator&comp = key_comparator(), const allocator_type& alloc = allocator_type()) : _comp (comp), _alloc_val (alloc)
	{
		std::cerr << std::endl << "yolo, we have a tree" << std::endl;
		this->_root = 0;

	}

	~Tree()
	{

	}

	Tree &operator=(const Tree &rhs)
	{
		//destroyBelow(_root);
		_root = 0;
		_comp = rhs._comp; 
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
		return node;
	}

//**********************************************************//
// Readers                                                  //
//**********************************************************//
// find, check if it has to be const
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
			printTree(getRoot());
		else if (node != 0)
		{
			std::cout << "Depth: " << i << " Key: " << node->value.first << " value: " << node->value.second << std::endl;
			if (node->left)
				printTree(node->left, i + 1);
			if (node->right)
				printTree(node->right, i + 1);
		}
		
	}

	Node *getRoot(void)
	{
		while (_root->parent)
			_root = _root->parent;
		return (_root);
	}
	Node *getMin(void)
	{	
		Node *res = _root;
		while (res->left)
			res = res->left;
		return res;
	}
	Node *getMax(void)
	{	
		Node *res = _root;
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

// operator []


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



};

}

#endif