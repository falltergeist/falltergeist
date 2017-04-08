/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
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

#ifndef FALLTERGEIST_FORMAT_FRM_FILE_H
#define FALLTERGEIST_FORMAT_FRM_FILE_H

// C++ standard includes
#include <map>
#include <vector>

// Falltergeist includes
#include "../Dat/Item.h"
#include "../Frm/Direction.h"
#include "../Enums.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}
namespace Pal
{
class File;
}
namespace Frm
{
class Direction;

class File : public Dat::Item
{
public:
    File(Dat::Stream&& stream);

    uint32_t version() const;
    uint16_t framesPerSecond() const;
    uint16_t framesPerDirection() const;
    uint16_t actionFrame() const;

    uint16_t width() const;

    uint16_t height() const;

    int16_t offsetX(unsigned int direction = 0, unsigned int frame = 0) const;
    int16_t offsetY(unsigned int direction = 0, unsigned int frame = 0) const;

    uint32_t* rgba(Pal::File* palFile);
    std::vector<bool>& mask(Pal::File* palFile);

    const std::vector<Direction>& directions() const;

protected:
    std::vector<uint32_t> _rgba;
    uint32_t _version = 0;
    uint16_t _framesPerSecond = 0;
    uint16_t _framesPerDirection = 0;
    uint16_t _actionFrame = 0;
    bool _animatedPalette = false;

    std::vector<Direction> _directions;
    std::vector<bool> _mask;
};

}
}
}
#endif // FALLTERGEIST_FORMAT_FRM_FILE_H
