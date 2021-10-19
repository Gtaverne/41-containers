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
	
	{
		ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::my_rev_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::my_rev_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';

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
		// arbol.insertNode(tmp_nd, ft::make_pair(12, 140));
		// arbol.insertNode(tmp_nd, ft::make_pair(200, 10));
		// arbol.insertNode(tmp_nd, ft::make_pair(15, 210));
		treegenerator(&arbol, 100);

		std::cout << "Root " << arbol.getRoot()->value.first << " " << arbol.getRoot()->value.second << std::endl;
		std::cout << "Min " << arbol.getMin()->value.first << " " << arbol.getMin()->value.second << std::endl;
		std::cout << "Max " << arbol.getMax()->value.first << " " << arbol.getMax()->value.second << std::endl;

		if ((tmp_nd = arbol.finder(15)))
		{
			std::cout << "FOUND key=15: " << tmp_nd->value.first << " " << tmp_nd->value.second << std::endl;
			std::cout << "Balance factor of 15: " << arbol.balanceFactor(tmp_nd) << std::endl << std::endl;
			std::cout << "Our node -> left: " << arbol.getHeight(tmp_nd->left) << std::endl << std::endl;
			std::cout << "Our node -> right: " << arbol.getHeight(tmp_nd->right) << std::endl << std::endl;
			arbol.printTree(0);
		}
	}
}
