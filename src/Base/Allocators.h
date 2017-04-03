/*
 * Copyright 2012-2017 Falltergeist Developers.
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

#ifndef FALLTERGEIST_BASE_ALLOCATORS_H
#define FALLTERGEIST_BASE_ALLOCATORS_H

namespace Falltergeist
{
namespace Base
{

// Allocator adaptor that interposes construct() calls to
// convert value initialization into default initialization.
// Taken from: http://stackoverflow.com/a/21028912/273767
// 
// Usage examples:
// - std::vector<char> (a buffer) - works as fast as plain new char[..] (after optimization) with benefits of automatic memory management
template <typename T, typename A = std::allocator<T>>
class default_init_allocator : public A {
    typedef std::allocator_traits<A> a_t;
public:
    template <typename U> struct rebind {
        using other =
            default_init_allocator<
            U, typename a_t::template rebind_alloc<U>
            >;
    };

    using A::A;

    template <typename U>
    void construct(U* ptr)
        noexcept(std::is_nothrow_default_constructible<U>::value) {
        ::new(static_cast<void*>(ptr)) U;
    }
    template <typename U, typename...Args>
    void construct(U* ptr, Args&&... args) {
        a_t::construct(static_cast<A&>(*this),
                       ptr, std::forward<Args>(args)...);
    }
};

}
}

#endif FALLTERGEIST_BASE_ALLOCATORS_H
