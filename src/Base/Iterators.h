/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_BASE_ITERATORS_H
#define FALLTERGEIST_BASE_ITERATORS_H

#include <list>
#include <memory>
#include <vector>

namespace Falltergeist
{

namespace Base
{

/**
 * Universal iterator wrapper for containers holding unique_ptr (or shared_ptr) to some type that returns plain pointer instead.
 * Useful when class holds collection of unique_ptr's and you wan't to iterate over it from outside without exposing unique_ptr.
 */
template <typename T, typename ContT, typename IterT>
class iterator_base_decorator : public std::iterator<std::forward_iterator_tag,T*>
{
    IterT _itr;

public:
    iterator_base_decorator<T, ContT, IterT>(IterT temp) : _itr(temp)
    {
    }

    iterator_base_decorator<T, ContT, IterT>(const iterator_base_decorator<T, ContT, IterT>& myitr) : _itr(myitr._itr)
    {
    }

    iterator_base_decorator<T, ContT, IterT>& operator ++()
    {
        _itr++;
        return *this;
    }

    iterator_base_decorator<T, ContT, IterT>& operator --()
    {
       _itr--;
        return *this;
    }

    bool operator ==(const iterator_base_decorator<T, ContT, IterT>& rhs)
    {
        return _itr == rhs._itr;
    }

    bool operator !=(const iterator_base_decorator<T, ContT, IterT>& rhs)
    {
        return _itr != rhs._itr;
    }

    iterator_base_decorator<T, ContT, IterT> operator ++(int)
    {
        iterator_base_decorator<T, ContT, IterT> result(*this);
        ++*this;
        return result;
    }

    iterator_base_decorator<T, ContT, IterT> operator --(int)
    {
        iterator_base_decorator<T, ContT, IterT> result(*this);
        --*this;
        return result;
    }

    T* operator ->()
    {
        return _itr->get();
    }

    T* operator *()
    {
        return _itr->get();
    }
};


template <typename T, typename ContT>
using iterator_decorator = iterator_base_decorator<T, ContT, typename ContT::const_iterator>;

template <typename T, typename ContT>
using const_iterator_decorator = iterator_base_decorator<T, ContT, typename ContT::const_iterator>;

template <typename T, typename ContT>
using reverse_iterator_decorator = iterator_base_decorator<T, ContT, typename ContT::reverse_iterator>;

template <typename T, typename ContT>
using const_reverse_iterator_decorator = iterator_base_decorator<T, ContT, typename ContT::const_reverse_iterator>;

/*
template <typename T>
using vector_iterator_decorator = iterator_decorator<T, std::vector<std::unique_ptr<T>>>;

template <typename T>
using vector_const_iterator_decorator = const_iterator_decorator<T, std::vector<std::unique_ptr<T>>>;

template <typename T>
using vector_reverse_iterator_decorator = reverse_iterator_decorator<T, std::vector<std::unique_ptr<T>>>;

template <typename T>
using vector_const_reverse_iterator_decorator = const_reverse_iterator_decorator<T, std::vector<std::unique_ptr<T>>>;

template <typename T>
using list_iterator_decorator = iterator_decorator<T, std::list<std::unique_ptr<T>>>;

template <typename T>
using list_const_iterator_decorator = const_iterator_decorator<T, std::list<std::unique_ptr<T>>>;

template <typename T>
using list_reverse_iterator_decorator = reverse_iterator_decorator<T, std::list<std::unique_ptr<T>>>;

template <typename T>
using list_const_reverse_iterator_decorator = const_reverse_iterator_decorator<T, std::list<std::unique_ptr<T>>>;
*/

/**
 * Decorator for vector of unique_ptr's that changes iterating behavior to return plain pointers automagically.
 */
template <typename T>
class vector_ptr_decorator
{
    using vector_t = std::vector<std::unique_ptr<T>>;

    vector_t& _cont;

public:
    using iterator = iterator_decorator<T, vector_t>;
    using const_iterator = const_iterator_decorator<T, vector_t>;
    using reverse_iterator = reverse_iterator_decorator<T, vector_t>;
    using const_reverse_iterator = const_reverse_iterator_decorator<T, vector_t>;

    vector_ptr_decorator(std::vector<std::unique_ptr<T>>& vec) : _cont(vec)
    {
    }

    iterator begin()                    { return iterator(_cont.begin()); }
    iterator end()                      { return iterator(_cont.end()); }
    const_iterator cbegin()             { return vector_ptr_decorator::const_iterator(_cont.cbegin()); }
    const_iterator cend()               { return vector_ptr_decorator::const_iterator(_cont.cend()); }
    reverse_iterator rbegin()           { return vector_ptr_decorator::reverse_iterator(_cont.rbegin()); }
    reverse_iterator rend()             { return vector_ptr_decorator::reverse_iterator(_cont.rend()); }
    const_reverse_iterator crbegin()    { return vector_ptr_decorator::const_reverse_iterator(_cont.crbegin()); }
    const_reverse_iterator crend()      { return vector_ptr_decorator::const_reverse_iterator(_cont.crend()); }
};


}

}

#endif //FALLTERGEIST_BASE_ITERATORS_H
