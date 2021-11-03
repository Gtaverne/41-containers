#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"


#include <cstddef>
#include <iostream>
#include <iterator>

namespace ft
{
	//https://www.cplusplus.com/reference/iterator/BidirectionalIterator/
	//Check here the possible operations

	template<class Node>
	class tree_iterator 
	{
	public:
		typedef Node value_type;
		typedef value_type *node_ptr;
		typedef typename Node::value_type data_type; //const?
		typedef data_type &reference;
		typedef data_type const &const_reference;
		typedef data_type *pointer;
		typedef data_type const *const_pointer;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		node_ptr node;

//**********************************************************//
// Canon                                                    //
//**********************************************************//

		tree_iterator() : node(), root(), NIL() {}

		tree_iterator(node_ptr node, node_ptr root, node_ptr NIL) : node(node), root(root), NIL(NIL) {}

		tree_iterator(const tree_iterator &src) : node(src.node), root(src.root), NIL(src.NIL) {}
		
		~tree_iterator (void) {}

		tree_iterator &operator=(tree_iterator const &src)
		{
			node = src.node;
			root = src.root;
			NIL = src.NIL;
			return *this;
		}

		//As for vector, we must have an overload operator for const iterators
		operator tree_iterator<value_type const > (void) const
		{
			std::cout << "Yes we cast" << std::endl;
			return (tree_iterator<value_type const> (node, root, NIL));
		}

//**********************************************************//
// operator                                                 //
//**********************************************************//

//map's underlying structure is a tree, so the memory location might not be contiguous:
// >, >=, <, <= make no sense

		friend bool operator==(const tree_iterator &lhs, const tree_iterator &rhs) {return lhs.node == rhs.node;}
		friend bool operator!=(const tree_iterator &lhs, const tree_iterator &rhs) {return lhs.node != rhs.node;}

//**********************************************************//
// Dereferencing                                            //
//**********************************************************//

		reference operator*(void) {return (node->val);}
		const_reference operator*(void) const {return (node->val);}
		pointer operator->(void) {return ( &(operator*()));}
		const_pointer operator->(void) const {return ( &(operator*()));}

//**********************************************************//
// Incrementations                                          //
//**********************************************************//

	tree_iterator &operator++(void)
	{
		if (node != NIL)
			node = _next();
		return *this;
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp(*this);
		++(*this);
		return (tmp);
	}

	tree_iterator &operator--(void)
	{
		if (node != NIL)
			node = _prev();
		else
			node = _max(root);
		return *this;
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
		--(*this);
		return (tmp);
	}

	private:

		node_ptr root;
		node_ptr NIL;

//**********************************************************//
// Utils for incrementations                                //
//**********************************************************//		
		
		node_ptr _max(node_ptr node)
		{
			while (node->right != NIL)
				node = node->right;
			return node;
		}

		node_ptr _min(node_ptr node)
		{
			while (node->left != NIL)
				node = node->left;
			return node;
		}

//Here we have a subtelty when we need to do end--, it should move to max since end is "beyond the end"
		node_ptr _prev(void)
		{
			node_ptr n = node;
			node_ptr previous = NIL;

			if (n->left != NIL)
				return _max(n->left);
			previous = n->parent;
			while (previous != NIL && n == previous->left)
			{
				n = previous;
				previous = previous->parent;
			}
			return previous;
		}

		node_ptr _next(void)
		{
			node_ptr n = node;
			node_ptr next = NIL;

			if (n->right != NIL)
				return _min(n->right);

			next = n->parent;
			while (next != NIL && n == next->right)
			{
				n = next;
				next = next->parent;
			}
			return next;
		}
	};

	

}

#endif