#include "common.hpp"

#define T1 int

int		main(void)
{
	TESTED_NAMESPACE::set<T1> st;
	TESTED_NAMESPACE::set<T1>::iterator it = st.begin(); 

	(void)it;
	return (0);
}
