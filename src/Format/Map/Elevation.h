﻿/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 Falltergeist Developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FALLTERGEIST_FORMAT_MAP_ELEVATION_H
#define FALLTERGEIST_FORMAT_MAP_ELEVATION_H

#include "../Map/Object.h"

#include <memory>
#include <vector>

namespace Falltergeist
{
namespace Format
{
namespace Map
{

class Elevation
{

public:
    Elevation();
    std::vector<std::unique_ptr<Object>>& objects();
    const std::vector<std::unique_ptr<Object>>& objects() const;
    std::vector<uint16_t>& floorTiles();
    const std::vector<uint16_t>& floorTiles() const;
    std::vector<uint16_t>& roofTiles();
    const std::vector<uint16_t>& roofTiles() const;

protected:
    std::vector<uint16_t> _floorTiles;
    std::vector<uint16_t> _roofTiles;
    std::vector<std::unique_ptr<Object>> _objects;

};

}
}
}
#endif // FALLTERGEIST_FORMAT_MAP_ELEVATION_H
