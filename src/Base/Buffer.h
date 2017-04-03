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

#ifndef FALLTERGEIST_BASE_BUFFER_H
#define FALLTERGEIST_BASE_BUFFER_H

namespace Falltergeist
{
namespace Base
{

// A thin wrapper over plain C-array.
// Handles allocation and deallocation of the underlying buffer.
// Does not perform any kind of initialization allocated of data.
template <typename T>
class Buffer {
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
    Buffer<T>(Buffer<T>&& other) : _buf(other._buf), _size(other._size)
    {
        other._buf = nullptr;
        other._size = 0;
    }

    // Move-assigns buffer pointer from another Buffer object
    Buffer<T>& operator= (Buffer<T>&& other)
    {
        _buf = other._buf;
        _size = other._size;
        other._buf = nullptr;
        other._size = 0;
    }

    Buffer<T>(const Buffer<T>&) = delete;
    Buffer<T>& operator= (const Buffer<T>&) = delete;

    ~Buffer<T>()
    {
        if (_buf) {
            delete[] _buf;
        }
    }

    // Reallocate the underlying buffer to the specified size
    // All data in buffer will be discarded
    void resize(size_t newSize)
    {
        if (_buf) {
            delete[] _buf;
        }
        if (newSize > 0) {
            _buf = new T[newSize];
        } else {
            _buf = nullptr;
        }
        _size = newSize;
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
    T* _buf;
    size_t _size;
};

}
}

#endif // FALLTERGEIST_BASE_BUFFER_H
