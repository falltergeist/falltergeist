#pragma once

#include <cstddef>

namespace Falltergeist
{
    namespace Base
    {
        // A thin wrapper over plain C-array.
        // Handles allocation and deallocation of the underlying buffer.
        // Does not perform any kind of initialization of allocated memory.
        template <typename T>
        class Buffer
        {
            public:
                // Creates new empty buffer
                Buffer<T>() : _size(0), _buf(nullptr)
                {
                }

                // Creates new buffer with given size
                Buffer<T>(size_t size) : _size(size)
                {
                    _buf = new T[size];
                }

                // Constructs by moving buffer pointer from another Buffer object
                Buffer<T>(Buffer<T>&& other) : _size(other._size), _buf(other._buf)
                {
                    other._size = 0;
                    other._buf = nullptr;
                }

                // Move-assigns buffer pointer from another Buffer object
                Buffer<T>& operator= (Buffer<T>&& other)
                {
                    _cleanUpBuffer();
                    _size = other._size;
                    _buf = other._buf;
                    other._size = 0;
                    other._buf = nullptr;
                    return *this;
                }

                Buffer<T>(const Buffer<T>&) = delete;
                Buffer<T>& operator= (const Buffer<T>&) = delete;

                ~Buffer<T>()
                {
                    _cleanUpBuffer();
                }

                // Access element at a given index. No bounds checking is performed.
                T& operator[] (size_t index)
                {
                    return _buf[index];
                }

                // Access element at a given index. No bounds checking is performed.
                const T& operator[] (size_t index) const
                {
                    return _buf[index];
                }

                T* begin()
                {
                    return &_buf[0];
                }

                T* end() {
                    return &_buf[_size];
                }

                // Reallocate the underlying buffer to the specified size
                // All data in buffer will be discarded
                void resize(size_t newSize)
                {
                    _cleanUpBuffer();
                    _size = newSize;
                    if (newSize > 0)
                    {
                        _buf = new T[newSize];
                    }
                    else
                    {
                        _buf = nullptr;
                    }
                }

                // The current size of data in buffer
                size_t size() const
                {
                    return _size;
                }

                // Returns true if the buffer is currently empty
                bool empty() const
                {
                    return _size == 0;
                }

                // The pointer to underlying buffer
                T* data()
                {
                    return _buf;
                }

                // The const pointer to underlying buffer
                const T* data() const
                {
                    return _buf;
                }

            private:
                size_t _size;
                T* _buf;

                void _cleanUpBuffer()
                {
                    if (_buf != nullptr)
                    {
                        delete[] _buf;
                    }
                }
        };
    }
}
