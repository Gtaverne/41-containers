#include "./sources/vector.hpp"
#include "./sources/map.hpp"
#include "./sources/stack.hpp"
#include <vector>
#include <stack>
#include <map>
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
std::cout << std::endl << "Vector string and vector of vector" << std::endl;
std::cout << "***Here comes the base case***" << std::endl;
	{
	std::vector<std::string>vec;
	std::vector<std::vector<std::string> >vecvec;
	testerStrtVec(vec, vecvec);
	}
std::cout << "***Here comes my version***" << std::endl;
	{
	ft::vector<std::string>vec;
	ft::vector<ft::vector<std::string> >vecvec;
	testerStrtVec(vec, vecvec);
	}

// //**********************************************************//
// // Testeur de stack                                         //
// //**********************************************************//
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
// Testeur de map                                           //
//**********************************************************//
std::cout << std::endl << "Map int" << std::endl;
std::cout << "***Here comes the base case***" << std::endl;
	{
	std::map<int, int> mymap;
	std::pair<int, int> tempaire;

	std::map<int, int>::iterator it = mymap.begin();
	std::map<int, int>::const_iterator itbis = mymap.begin();

	itbis = it;

	it = mymap.end();

	for (int i = 0; i < 10; i++)
		mymap.insert(std::pair<int, int>(i + 10, 10 * i));
	testerIntMap(mymap, tempaire);
	std::cout << "tempaire.first " << tempaire.first << std::endl;

	}

std::cout << std::endl << "***Here comes my version***" << std::endl;
	{
	ft::map<int, int> mymap;
	ft::pair<int, int> tempaire;

	ft::map<int, int>::iterator it = mymap.begin();
	ft::map<int, int>::const_iterator itbis = mymap.begin();
	
	it->second = 12;
	for (int i = 0; i < 10; i++)
		mymap.insert(ft::pair<int, int>(i + 10, 10 * i));
	testerIntMap (mymap, tempaire);

	std::cout << "tempaire.first " << tempaire.first << std::endl;

	}

}
