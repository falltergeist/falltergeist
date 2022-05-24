#pragma once

// Project includes

// Third-party includes

// stdlib
#include <functional>
#include <vector>

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
