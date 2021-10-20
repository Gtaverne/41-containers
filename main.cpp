#include "./sources/vector.hpp"
#include "./sources/map.hpp"
#include "./sources/stack.hpp"
#include <vector>
#include <stack>
#include "mytestes.hpp"
#include <typeinfo>


int main ()
{
srand(time(NULL));
//**********************************************************//
// Testeur de vector, int                                   //
//**********************************************************//
std::cout << std::endl << "Vector int" << std::endl;
std::cout << "***Here comes the base case***" << std::endl;
	{
	std::vector<int> vec;
	testerIntVec(vec);
	}

std::cout << std::endl << "***Here comes my version***" << std::endl;
	{
	ft::vector<int> vec;
	testerIntVec(vec);
	}

// //**********************************************************//
// // Testeur de vector, std::string                           //
// //**********************************************************//
// std::cout << std::endl << "Vector string" << std::endl;
// std::cout << "***Here comes the base case***" << std::endl;
// 	{
// 	std::vector<std::string>vec;
// 	testerStrtVec(vec);
// 	}
// std::cout << "***Here comes my version***" << std::endl;
// 	{
// 	ft::vector<std::string>vec;
// 	testerStrtVec(vec);
// 	}

// //**********************************************************//
// // Testeur de stack                                         //
// //**********************************************************//
// std::cout << std::endl << "Stack" << std::endl;
// std::cout << "***Here comes the base case***" << std::endl;
// 	{
// 	std::pair<int, std::string> p1;
// 	std::pair<int, std::string> p2 (2, "42");
// 	p1 = std::make_pair<int, std::string>(12, "dudule");
// 	pairtest(p1, p2);
// 	}
// std::cout << "***Here comes my version***" << std::endl;
// 	{
// 	ft::pair<int, std::string> p1;
// 	ft::pair<int, std::string> p2 (2, "42");
// 	p1 = ft::make_pair<int, std::string>(12, "dudule");
// 	pairtest(p1, p2);
// 	}

//**********************************************************//
// Testeur de tree                                          //
//**********************************************************//
std::cout << std::endl << "Tree" << std::endl;
std::cout << "***Here comes my tree***" << std::endl;
	{
		ft::Tree<ft::pair<int, int> > arbol;
		ft::Tree<ft::pair<int, int> >::Node *tmp_nd;

		treegenerator(&arbol, 50);

		std::cout << "Root " << arbol.getRoot()->value.first << " " << arbol.getRoot()->value.second << std::endl;
		std::cout << "Min " << arbol.getMin()->value.first << " " << arbol.getMin()->value.second << std::endl;
		std::cout << "Max " << arbol.getMax()->value.first << " " << arbol.getMax()->value.second << std::endl;

		if ((tmp_nd = arbol.finder(20)))
		{
			std::cout << "FOUND key=15: " << tmp_nd->value.first << " " << tmp_nd->value.second << std::endl;
			std::cout << "Balance factor of 15: " << arbol.balanceFactor(tmp_nd) << std::endl << std::endl;
			std::cout << "Our node -> left: " << arbol.getHeight(tmp_nd->left) << std::endl << std::endl;
			std::cout << "Our node -> right: " << arbol.getHeight(tmp_nd->right) << std::endl << std::endl;
		}
		arbol.printTree(0);
		ft::Tree<ft::pair<int, int> > treecopy;
		treecopy = arbol;
		treecopy.printTree(0);

		std::cout << std::endl << "We want to delete key=5" << std::endl;
		treecopy.delete_node(treecopy.getRoot(), 5);
		treecopy.printTree(0);


	}
}
