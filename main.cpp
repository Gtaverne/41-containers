#include "./sources/vector.hpp"
#include "./sources/map.hpp"
#include "./sources/stack.hpp"
#include <vector>
#include <stack>
#include "mytestes.hpp"
#include <typeinfo>


int main ()
{
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

//**********************************************************//
// Testeur de vector, std::string                           //
//**********************************************************//
std::cout << std::endl << "Vector string" << std::endl;
std::cout << "***Here comes the base case***" << std::endl;
	{
	std::vector<std::string>vec;
	testerStrtVec(vec);
	}
std::cout << "***Here comes my version***" << std::endl;
	{
	ft::vector<std::string>vec;
	testerStrtVec(vec);
	}

//**********************************************************//
// Testeur de stack                                         //
//**********************************************************//
std::cout << std::endl << "Stack" << std::endl;
std::cout << "***Here comes the base case***" << std::endl;
	{
	std::pair<int, std::string> p1;
	std::pair<int, std::string> p2 (2, "42");
	p1 = std::make_pair<int, std::string>(12, "dudule");
	pairtest(p1, p2);
	}
std::cout << "***Here comes my version***" << std::endl;
	{
	ft::pair<int, std::string> p1;
	ft::pair<int, std::string> p2 (2, "42");
	p1 = ft::make_pair<int, std::string>(12, "dudule");
	pairtest(p1, p2);
	}

//**********************************************************//
// Testeur de tree                                          //
//**********************************************************//
std::cout << std::endl << "Stack" << std::endl;
std::cout << "***Here comes the base case***" << std::endl;
	{
		ft::Tree<ft::pair<int, int> > arbol;

	}
}
