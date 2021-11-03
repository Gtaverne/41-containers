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
		typedef data_type *pointer;
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
		
	reference operator*(void) const {return (node->val);}
	pointer operator->(void) const {return ( &(operator*()));}

	reference operator*(void) {return (node->val);}
	pointer operator->(void) {return ( &(operator*()));}

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

		node_ptr root;
		node_ptr NIL;
	
	private:

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


//********************************************************************************************************//
// Const Iterator                                                                                         //
//********************************************************************************************************//


	template<class Node>
	class const_tree_iterator 
	{
	public:
		typedef Node value_type;
		typedef value_type *node_ptr;
		typedef typename Node::value_type data_type; //const?
		typedef const data_type &reference;
		typedef const data_type *pointer;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		node_ptr node;

//**********************************************************//
// Canon                                                    //
//**********************************************************//

		const_tree_iterator() : node(), root(), NIL() {}

		const_tree_iterator(node_ptr node, node_ptr root, node_ptr NIL) : node(node), root(root), NIL(NIL) {}

		const_tree_iterator(const const_tree_iterator &src) : node(src.node), root(src.root), NIL(src.NIL) {}
		
		const_tree_iterator(const tree_iterator<value_type> &src) : node(src.node), root(src.root), NIL(src.NIL) {}

		~const_tree_iterator (void) {}

		const_tree_iterator &operator=(const_tree_iterator const &src)
		{
			node = src.node;
			root = src.root;
			NIL = src.NIL;
			return *this;
		}

		//As for vector, we must have an overload operator for const iterators
		operator const_tree_iterator<value_type const > () const
		{
			std::cout << "Yes we cast" << std::endl;
			return (const_tree_iterator<value_type const> (node, root, NIL));
		}

//**********************************************************//
// operator                                                 //
//**********************************************************//

//map's underlying structure is a tree, so the memory location might not be contiguous:
// >, >=, <, <= make no sense

		friend bool operator==(const const_tree_iterator &lhs, const const_tree_iterator &rhs) {return lhs.node == rhs.node;}
		friend bool operator!=(const const_tree_iterator &lhs, const const_tree_iterator &rhs) {return lhs.node != rhs.node;}

//**********************************************************//
// Dereferencing                                            //
//**********************************************************//

		reference operator*(void) const {return (node->val);}
		pointer operator->(void) const {return ( &(operator*()));}

		reference operator*(void) {return (node->val);}
		pointer operator->(void) {return ( &(operator*()));}

//**********************************************************//
// Incrementations                                          //
//**********************************************************//

	const_tree_iterator &operator++(void)
	{
		if (node != NIL)
			node = _next();
		return *this;
	}

	const_tree_iterator operator++(int)
	{
		const_tree_iterator tmp(*this);
		++(*this);
		return (tmp);
	}

	const_tree_iterator &operator--(void)
	{
		if (node != NIL)
			node = _prev();
		else
			node = _max(root);
		return *this;
	}

	const_tree_iterator operator--(int)
	{
		const_tree_iterator tmp(*this);
		--(*this);
		return (tmp);
	}

//**********************************************************//
// Overloading toward const                                 //
//**********************************************************//


		node_ptr root;
		node_ptr NIL;

	private:


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


//**********************************************************//
// Used to compare const and regular iterators              //
//**********************************************************//
	template <typename Iter1, typename Iter2>
	bool operator==(const tree_iterator<Iter1>& lhs, const const_tree_iterator<Iter2>& rhs)
	{return lhs.node == rhs.node;};

	template <typename Iter1, typename Iter2>
	bool operator==(const const_tree_iterator<Iter1>& lhs, const tree_iterator<Iter2>& rhs)
	{return lhs.node == rhs.node;};

	template <typename Iter1, typename Iter2>
	bool operator!=(const tree_iterator<Iter1>& lhs, const const_tree_iterator<Iter2>& rhs)
	{return lhs.node != rhs.node;};

	template <typename Iter1, typename Iter2>
	bool operator!=(const const_tree_iterator<Iter1>& lhs, const tree_iterator<Iter2>& rhs)
	{return lhs.node != rhs.node;};

}

#endif