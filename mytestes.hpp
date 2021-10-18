#ifndef MYTESTES_HPP
#define MYTESTES_HPP

#include "./sources/vector.hpp"
#include "./sources/stack.hpp"
#include "./sources/pair.hpp"
#include <iostream>

//None of those function is mandatory. Just my own tests

template <class anyintvector>
void testerIntVec(anyintvector vec)
{
	std::cout << "Initial capacity " << vec.capacity() << std::endl;
	std::cout << "Initial empty " << vec.empty() << std::endl;
	for (int i = 0; i < 100 ; i++)
		vec.push_back(i * 5);
	vec[0] = 42;
	typename anyintvector::const_iterator bob = vec.begin();
	std::cout << "vec[]: " << vec[0] << std::endl;
	std::cout << *bob << std::endl;

	std::cout << "size " << vec.size() << std::endl;
	std::cout << "max_size " << vec.max_size() << std::endl;

	std::cout << "capacity " << vec.capacity() << std::endl;
	vec.resize(10);
	std::cout << "Capacity ainter resize " << vec.capacity() << std::endl;
	std::cout << "empty " << vec.empty() << std::endl;

	//iterators
	std::cout << "TEST OF ITERATORS" << std::endl;
	std::cout << "begin " << *vec.begin() << std::endl;
	std::cout << "== " << (vec.end() == vec.begin()) << std::endl;
	std::cout << "incremented + 5: " << *((vec.begin() + 0)) << std::endl;
	std::cout << "end " << *(vec.end()) << std::endl;
	std::cout << "[] operator " << vec.begin()[8] << std::endl;
	std::cout << "at " << vec.at(8) << std::endl;
}

template <class stringvec>
void testerStrtVec(stringvec vec)
{
	std::cout << "Initial capacity " << vec.capacity() << std::endl;
	std::cout << "Initial empty " << vec.empty() << std::endl;
	for (int i = 0; i < 100 ; i++)
		vec.push_back("bob");
	vec[11] = "maurice";
	typename stringvec::iterator bob = vec.begin() + 10;
	std::cout << "vec[]: " << vec[0] << std::endl;
	std::cout << "size " << vec.size() << std::endl;
	std::cout << *bob << std::endl;
	vec.erase(bob);
	std::cout << "size after erase " << vec.size() << std::endl;
	std::cout << *bob << std::endl;
}

template <typename anypair1, typename anypair2>
void pairtest(anypair1 pair1, anypair2 pair2)
{
	pair1.first = 1;
	pair1.second += " for president";
	std::cout << "pair1 == pair2: " << (pair1 == pair2) << std::endl;
	anypair2 nioupair(pair2);
	std::cout << "nioupair(pair2) == pair2: "<< (nioupair == pair2) << std::endl;
}

#endif
