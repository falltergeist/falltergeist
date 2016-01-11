/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_BASE_STLFEATURES_H
#define FALLTERGEIST_BASE_STLFEATURES_H

// C++ standard includes
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Base
{
namespace Detail
{

template<class T> struct UniqueIf
{
    typedef std::unique_ptr<T> SingleObject;
};

template<class T> struct UniqueIf<T[]>
{
    typedef std::unique_ptr<T[]> UnknownBound;
};

template<class T, std::size_t N> struct UniqueIf<T[N]>
{
    typedef void KnownBound;
};

}  // namespace Detail

template<class T, class... Args>
inline typename Detail::UniqueIf<T>::SingleObject
make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
inline typename Detail::UniqueIf<T>::UnknownBound
make_unique(std::size_t n)
{
    typedef typename std::remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
inline typename Detail::UniqueIf<T>::KnownBound
make_unique(Args&&...) = delete;

}
}
#endif // FALLTERGEIST_BASE_STLFEATURES_H
