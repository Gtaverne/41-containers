#include "./sources/Vector.hpp"
#include "./sources/Map.hpp"
#include "./sources/Stack.hpp"
#include <vector>
#include "test/test.hpp"


int main ()
{
//**********************************************//
// Testeur de vecteur                           //
//**********************************************//
	{
	std::vector<int> vec;
	std::cout << "Initial capacity " << vec.capacity() << std::endl;
	for (int i = 0; i < 100 ; i++)
		vec.push_back(i);
	std::cout << "vec[33]: " << vec[33] << std::endl;

	std::cout << "size " << vec.size() << std::endl;
	std::cout << "max_size " << vec.max_size() << std::endl;

	std::cout << "capacity " << vec.capacity() << std::endl;
	vec.resize(10000);
	std::cout << "Capacity after resize " << vec.capacity() << std::endl;
	std::cout << "empty " << vec.empty() << std::endl;
	}

//**********************************************//
// Testeur de ft::vector                        //
//**********************************************//
std::cout << std::endl << "Here comes my tester " << std::endl;

	{
	ft::vector<int> vec;
	std::cout << "Initial capacity " << vec.capacity() << std::endl;
	std::cout << "Initial empty " << vec.empty() << std::endl;
	for (int i = 0; i < 100 ; i++)
		vec.push_back(i);
	std::cout << "vec[33]: " << vec[33] << std::endl;

	std::cout << "size " << vec.size() << std::endl;
	std::cout << "max_size " << vec.max_size() << std::endl;

	std::cout << "capacity " << vec.capacity() << std::endl;
	vec.resize(10000);
	std::cout << "Capacity after resize " << vec.capacity() << std::endl;
	std::cout << "empty " << vec.empty() << std::endl;

	}

	
}
