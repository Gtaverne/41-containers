#ifndef MYTESTES_HPP
#define MYTESTES_HPP

#include "./sources/vector.hpp"
#include "./sources/stack.hpp"
#include "./sources/pair.hpp"
#include "./sources/map.hpp"


#include <iostream>

#include <time.h>
#include <stdlib.h>

//None of those function is mandatory. Just my own tests

template <class anyintvector>
void testerIntVec(anyintvector &vec)
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
	std::cout << "end " << *(vec.end() - 1) << std::endl;
	std::cout << "[] operator " << vec.begin()[8] << std::endl;
	std::cout << "at " << vec.at(8) << std::endl;
}

template <class stringvec, class vecception>
void testerStrtVec(stringvec &vec, vecception &vecvec)
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

	std::cout << "vecvec capacity: " << vecvec.capacity() << std::endl;
	for (int i = 0; i < 100 ; i++)
		vecvec.push_back(vec);
	
	std::cout << "vecvec[10][12] " << (vecvec[10][12]) << std::endl;


}

template <typename anypair1, typename anypair2>
void pairtest(anypair1 &pair1, anypair2 &pair2)
{
	pair1.first = 1;
	pair1.second += " for president";
	std::cout << "pair1 == pair2: " << (pair1 == pair2) << std::endl;
	anypair2 nioupair(pair2);
	std::cout << "nioupair(pair2) == pair2: "<< (nioupair == pair2) << std::endl;
}

template < typename Tree>
void treegenerator(Tree *tr, int len = 20)
{
	for (int i = 0 ; i < len; i++)
	{
		const int k = i - len / 2;
		tr->insertValue(ft::make_pair(k, rand() % 1000));
	}
}


template <class anymap, class anypair>
void testerIntMap(anymap &mymap, anypair &paire)
{

	
	std::cout << "Size: " << mymap.size() << std::endl;
	std::cout << "Max size: " << mymap.max_size() << std::endl;
	//mymap[25] = 5724;
	//std::cout << "map[25]: " << mymap[25] << std::endl;
	anymap tmp;
	typename anymap::iterator it = mymap.begin();
	typename anymap::iterator fin(mymap.end());
	typename anymap::const_iterator c_it(mymap.begin());
	typename anymap::iterator up =  ++(++mymap.begin());
	typename anymap::reverse_iterator r_it = mymap.rend();
	typename anymap::const_reverse_iterator c_r_it = mymap.rend();

	std::cout << "Iterators exist" << std::endl;

	tmp = mymap;
	paire.first = -10;
	paire.second = 1000;

	fin = it;
	//fin = mymap.insert(it, paire);
	c_it = it;
	std::cout << "it->first: " << (it->first) << std::endl;
	std::cout << "fin->first: " << (fin->first) << std::endl;
	std::cout << "fin->second: " << (fin->second) << std::endl;

	std::cout << "up->second: " << (up->second) << std::endl;

	
	fin = it;
	fin++;
	std::cout << "it == it: " << (it == it) << std::endl;
	std::cout << "it != it: " << (it != it) << std::endl;
	std::cout << "it != fin: " << (it != fin) << std::endl;
	std::cout << "it == fin: " << (it == fin) << std::endl;


	std::cout << "r_it == c_r_it: " << (r_it == c_r_it) << std::endl;


	// anypair tempaire = paire;
	// tempaire.first = 42;
	// tempaire.second = 84;

	std::cout << "it == it: " << (it == it) << std::endl;
	std::cout << "it == c_it: " << (it == c_it) << std::endl;

	std::cout << "it == fin: " << (it == fin) << std::endl;
	while (it != up)
		it++;
	std::cout << "it == tmp: " << (it == up) << std::endl;

	mymap.erase(--mymap.end());
	std::cout << "We killed end" << std::endl;
	mymap.erase(mymap.begin(), mymap.end());
	std::cout << "Is the map really empty: " << mymap.empty() << std::endl;
	for (int i = 0; i < 10 ; i++)
	{
		paire.first = i;
		paire.second = 15 + i;
		mymap.insert(paire);
	}
	std::cout << "A couple insertions, now len is: " << mymap.size() << std::endl;

}

#endif
