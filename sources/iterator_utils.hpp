#ifndef ITERATOR_UTILS_HPP
#define ITERATOR_UTILS_HPP

#include <iterator>
#include <cstddef>

namespace ft
{
//**********************************************//
// Iterator traits                              //
//**********************************************//

//Go try to understand this: https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/iterator_traits.html

    template <class Iterator>
    class iterator_traits {
    public:
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template <class T>
    class iterator_traits<T*> {
    public:
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T*> {
    public:
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef const T*                   pointer;
        typedef const T&                   reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

//***************************************************************//
// Equals, see https://en.cppreference.com/w/cpp/algorithm/equal //
//***************************************************************//

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
    while (first1 != last1)
    {
        if (*first1 != *first2)
            return false;
        first1++;
        first2++;
    }
    return true;
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
{
    while (first1 != last1)
    {
        if (!p(*first1, *first2))
            return false;
        first1++;
        first2++;
    }
    return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
    while (first1 != last1)
    {
        if (first2 == last2 || *first2 < *first1)
            return false;
        else if (*first1 < *first2)
            return true;
        first1++;
        first2++;
    }
    return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
    while (first1 != last1)
    {
        if (first2 == last2 || comp(*first2, *first1))
            return false;
        else if (comp(*first1, *first2))
            return true;
        first1++;
        first2++;
    }
    return (first2 != last2);
}

//**********************************************//
// Enable_if                                    //
//**********************************************//
}

#endif