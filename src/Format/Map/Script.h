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

#ifndef FALLTERGEIST_FORMAT_MAP_SCRIPT_H
#define FALLTERGEIST_FORMAT_MAP_SCRIPT_H

// C++ standard includes
#include <cstdint>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Map
{

// TODO: replace with struct
class Script
{
public:
    enum class Type
    {
        SYSTEM = 0,
        SPATIAL,
        TIMER,
        ITEM,
        CRITTER

    };

    int32_t PID() const;
    void setPID(int32_t PID);

    int32_t scriptId() const;
    void setScriptId(int32_t value);

    Type type() const;
    void setType(Type type);

    void setSpatialTile(uint32_t tile);
    uint32_t spatialTile() const;

    void setSpatialRadius(uint32_t radius);
    uint32_t spatialRadius() const;

    void setTimerTime(uint32_t time);
    uint32_t timerTime() const;

private:
    int32_t _PID = 0;
    int32_t _scriptId = -1;
    uint32_t _spatialTile = 0;
    uint32_t _spatialRadius = 0;
    uint32_t _timerTime = 0;

    Type _type;
};

}
}
}
#endif // FALLTERGEIST_FORMAT_MAP_SCRIPT_H
