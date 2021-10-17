#ifndef PAIR_HPP
#define PAIR_HPP


namespace ft
{
	template <class T1, class T2>
	class pair
	{
	public:

		typedef T1 type1;
		typedef T2 type2;

		type1 first;
		type2 second;

	//Canon
		pair(): first(), second() {}
		template<class U, class V>
		pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}
		pair (const type1& a, const type2& b): first(a), second(b) {}

		pair & operator= (const pair &rhs)
		{
			if (*this == rhs)
				return *this;
			this->first = rhs.first;
			this->second = rhs.second;
			return *this;
		}
	};

//**********************************************//
// Non member functions overload                //
//**********************************************//

// relational operators :https://www.cplusplus.com/reference/utility/pair/operators/

template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{return lhs.first==rhs.first && lhs.second==rhs.second;}

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{return !(lhs==rhs);}

template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);}

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{return !(rhs<lhs);}

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{return rhs<lhs;}

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{return !(lhs<rhs); }

template <class T1, class T2>
pair<T1,T2> make_pair (T1 x, T2 y) {return ( pair<T1,T2>(x,y) );}

}


#endif