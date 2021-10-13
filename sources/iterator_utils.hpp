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
        typedef const T*                         pointer;
        typedef const T&                         reference;
        typedef std::random_access_iterator_tag iterator_category;
    };


//**********************************************//
// Enable_if                                    //
//**********************************************//
}

#endif