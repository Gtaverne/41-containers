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

insertNode
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


		Node *getRoot(void)
		{
			Node *res = this;
			while (res->parent)
				res = res->parent;
			return (res);
		}
		Node *getMin(void)
		{	
			Node *res = this;
				while (res->left)
			return res;
		}
		Node *getMax(void)
		{	
			Node *res = this;
				while (res->right)
			return res;
		}


	};

private:
	key_comparator _comp;
	allocator_type _alloc_val;
	std::allocator<Node> _alloc_node;
	Node* _root;

	
public:
//**********************************************************//
// Canon                                                    //
//**********************************************************//

	Tree (const key_comparator&comp = key_comparator(), const allocator_type& alloc = allocator_type()) : _comp (comp), _alloc_val (alloc)
	{
		std::cerr << "yolo, we have a tree" << std::endl;
		this->_root = 0;

	}

	Tree &operator=(const Tree &rhs)
	{
		//destroyBelow(_root);
		_root = 0;
		_comp = rhs._comp; 
		return *this;
	}

//**********************************************************//
// Canon                                                    //
//**********************************************************//
	void printTree(Node *node, int i = 0)
	{
		if (!node && i != 0)
			printTree(_root);
		else
		{
			std::cout << i << "Key: " << node->value.first << " value: " << node->value.second << std::endl;
			if (node->left)
				printTree(node->left, ++i);
			if (node->right)
				printTree(node->right, ++i);
		}
		
	}


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
		//introduce the pivot here
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

// max
// min
// operator []


//**********************************************************//
// Balancers                                                //
//**********************************************************//



};

}

#endif