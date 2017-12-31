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

#ifndef FALLTERGEIST_BASE_DELEGATE_H
#define FALLTERGEIST_BASE_DELEGATE_H

// C++ standard includes
#include <functional>
#include <vector>

// Falltergeist includes

namespace Falltergeist
{
namespace Base
{

template <typename ...ArgT>
class Delegate
{
public:
    using Functor = std::function<void(ArgT...)>;
    using FunctorCollection = std::vector<Functor>;

    Delegate<ArgT...>() {}

    Delegate<ArgT...>(Functor func)
    {
        add(func);
    }

    void add(Functor func)
    {
        _functors.emplace_back(std::move(func));
    }

    void add(const Delegate<ArgT...>& other)
    {
        for (auto& func : other.functors())
        {
            add(func);
        }
    }

    void clear()
    {
        _functors.clear();
    }

    void invoke(ArgT... args)
    {
        for (auto& func : _functors)
        {
            func(args...);
        }
    }

    const FunctorCollection& functors() const
    {
        return _functors;
    }

    Delegate<ArgT...>& operator =(Functor func)
    {
        clear();
        add(std::move(func));
        return *this;
    }

    Delegate<ArgT...>& operator=(std::nullptr_t)
    {
        clear();
        return *this;
    }

    Delegate<ArgT...>& operator +=(Functor func)
    {
        add(std::move(func));
        return *this;
    }

    Delegate<ArgT...>& operator+=(const Delegate<ArgT...>& other)
    {
        add(other);
        return *this;
    }

    void operator () (ArgT... args)
    {
        invoke(std::forward<ArgT...>(args)...);
    }

    explicit operator bool () const
    {
        return _functors.size() > 0;
    }

private:
    FunctorCollection _functors;

};

}
}

#endif //FALLTERGEIST_BASE_DELEGATE_H
