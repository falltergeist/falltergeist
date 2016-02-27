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

// C++ standard includes
#include <algorithm>

// Falltergeist includes
#include "../Enums.h"
#include "../Frm/Direction.h"
#include "../Frm/File.h"
#include "../Frm/Frame.h"
#include "../Pal/File.h"
#include "../Pal/Color.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Frm
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream * stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
    for (auto direction : _directions)
    {
        delete direction;
    }
    delete [] _rgba;
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    _version = uint32();
    _framesPerSecond = uint16();
    _actionFrame = uint16();
    _framesPerDirection = uint16();

    uint16_t shiftX[6];
    uint16_t shiftY[6];
    uint32_t dataOffset[6];
    for (unsigned int i = 0; i != 6; ++i) shiftX[i] = uint16();
    for (unsigned int i = 0; i != 6; ++i) shiftY[i] = uint16();
    for (unsigned int i = 0; i != 6; ++i)
    {
        dataOffset[i] = uint32();
        if (i > 0 && dataOffset[i-1] == dataOffset[i])
        {
            continue;
        }

        auto direction = new Direction();
        direction->setDataOffset(dataOffset[i]);
        direction->setShiftX(shiftX[i]);
        direction->setShiftY(shiftY[i]);
        _directions.push_back(direction);
    }

    // for each direction
    for (auto direction : _directions)
    {
        // jump to frames data at frames area
        Dat::Item::setPosition(direction->dataOffset() + 62);

        // read all frames
        for (unsigned i = 0; i != _framesPerDirection; ++i)
        {            
            uint16_t width = uint16();
            uint16_t height = uint16();
            auto frame = new Frame(width, height);

            // Number of pixels for this frame
            // We don't need this, because we already have width*height
            uint32();

            frame->setOffsetX(int16());
            frame->setOffsetY(int16());

            // Pixels data
            for (unsigned y = 0; y != frame->height(); ++y)
            {
                for (unsigned x = 0; x != frame->width(); ++x)
                {
                    frame->setIndex(x, y, uint8());
                }
            }
            direction->frames()->push_back(frame);
        }
    }
}

uint32_t File::version() const
{
    return _version;
}

uint16_t File::framesPerSecond() const
{
    return _framesPerSecond;
}

uint16_t File::framesPerDirection() const
{
    return _framesPerDirection;
}

uint16_t File::actionFrame() const
{
    return _actionFrame;
}

std::vector<Direction*>* File::directions()
{
    return &_directions;
}

uint16_t File::width() const
{
    std::vector<uint16_t> widths;
    for (auto direction : _directions)
    {
        widths.push_back(direction->width());
    }
    return *std::max_element(widths.begin(), widths.end());
}

uint16_t File::height() const
{
    uint16_t height = 0;

    for (auto direction : _directions)
    {
        height += direction->height();
    }
    return height;
}

uint32_t* File::rgba(Pal::File* palFile)
{
    if (_rgba) return _rgba;
    _rgba = new uint32_t[width()*height()]();

    uint16_t w = width();

    unsigned positionY = 1;
    for (auto direction : _directions)
    {
        unsigned positionX = 1;
        for (auto frame : *direction->frames())
        {
            for (unsigned y = 0; y != frame->height(); ++y)
            {
                for (unsigned x = 0; x != frame->width(); ++x)
                {
                    _rgba[((y + positionY)*w) + x + positionX] = *palFile->color(frame->index(x, y));
                }
            }
            positionX += frame->width()+2;
        }
        positionY += direction->height();
    }
    return _rgba;
}

std::vector<bool>* File::mask(Pal::File* palFile)
{
    if (!_mask.empty()) return &_mask;

    uint16_t w = width();
    uint16_t h = height();

    _mask.resize(w*h, true);

    unsigned positionY = 0;
    for (auto direction : _directions)
    {
        unsigned positionX = 0;
        for (auto frame : *direction->frames())
        {
            for (unsigned y = 0; y != frame->height(); ++y)
            {
                for (unsigned x = 0; x != frame->width(); ++x)
                {
                    _mask[((y + positionY)*w) + x + positionX] = (palFile->color(frame->index(x, y))->alpha() > 0);
                }
            }
            positionX += frame->width();
        }
        positionY += direction->height();
    }
    return &_mask;
}

int16_t File::offsetX(unsigned int direction, unsigned int frame) const
{
    if (direction >= _directions.size()) direction = 0;
    return _directions.at(direction)->frames()->at(frame)->offsetX();
}

int16_t File::offsetY(unsigned int direction, unsigned int frame) const
{
    if (direction >= _directions.size()) direction = 0;
    return _directions.at(direction)->frames()->at(frame)->offsetY();
}

}
}
}
