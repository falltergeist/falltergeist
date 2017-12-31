/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#ifndef FALLTERGEIST_BASE_SINGLETON_H
#define FALLTERGEIST_BASE_SINGLETON_H

// C++ standard includes
#include <new>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Base
{

// Attention: this is NOT a thread-safe implementation of a Singleton pattern!
// If needed it will be easy to implement thread-safe behavior using
// C++11 atomics.
template <typename Type>
class Singleton
{
private:
    // Classes using the Singleton<T> pattern should declare a getInstance()
    // method and call Singleton::get() from within that.
    friend Type* Type::getInstance();

    static Type* get()
    {
        if (!_instance)
        {
            _instance = new Type();
        }

        return _instance;
    }

    static Type* _instance;
};

template <typename Type>
Type* Singleton<Type>::_instance = nullptr;

}
}
#endif // FALLTERGEIST_BASE_SINGLETON_H
