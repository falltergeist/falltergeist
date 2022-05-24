#pragma once

// Project includes

// Third-party includes

// stdlib
#include <new>

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
