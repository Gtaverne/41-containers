#include "./sources/Vector.hpp"
#include "./sources/Map.hpp"
#include "./sources/Stack.hpp"
#include <vector>
#include "test/test.hpp"


int main ()
{
	std::vector<int> vec;
	vec.push_back(1022);
	std::cout << vec[0] << std::endl;

	try
	{
		vec[364] = 15242;
		std::cout << vec[364] << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


	ftest::abitbol<float> ab;
	ab = 12.01;
	std::cout << ab.getArr() << std::endl;

	ftest::vector<char> str;
	
	std::string s = "Ein zwei drei";
	
	for (uint i = 0; i < s.size(); i++)
	{
		str.pushback(s[i]);
	}


	for (uint i = 0; i < s.size(); i++)
	{
		std::cout << str[i];
	}
	std::cout << std::endl << "Aren't you entertained?" << std::endl;
	try
	{
		str[100] = 'o';
		std::cout << str[100] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}
