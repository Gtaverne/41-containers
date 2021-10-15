#ifndef PAIR_HPP
#define PAIR_HPP

template <class T1, class T2>
class pair
{
public:

	typedef T1 type1;
	typedef T2 type2;

	type1 first_el;
	type2 sec_el;

//Canon
	pair(): first_el(NULL), sec_el(NULL) {}
	template<class U, class V>
	pair (const pair<U,V>& pr): first_el(pr.first_el), sec_el(pr.sec_el) {}
	pair (const type1& a, const type2& b): first_el(a), sec_el(b) {}

	pair & operator= (const pair &rhs)
	{
		if (*this == rhs)
			return *this;
		this->first_el = rhs.first_el;
		this->sec_el = rhs.sec_el;
		return *this;
	}
	

};




#endif