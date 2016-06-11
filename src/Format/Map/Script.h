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
    Script();
    ~Script();

    int32_t PID() const;
    void setPID(int32_t PID);

    int32_t scriptId() const;
    void setScriptId(int32_t value);

    Type type();
    void setType(Type type);

    void setSpatialTile(uint32_t tile);
    uint32_t spatialTile();

    void setSpatialRadius(uint32_t radius);
    uint32_t spatialRadius();

    void setTimerTime(uint32_t time);
    uint32_t timerTime();
protected:
    int32_t _PID = 0;
    int32_t _scriptId = -1;
    int32_t _unknown1 = 0;
    uint32_t _spatialTile = 0;
    uint32_t _spatialRadius = 0;
    uint32_t _timerTime = 0;
    int32_t _unknown4 = 0;
    int32_t _unknown5 = 0;
    int32_t _unknown6 = 0;
    int32_t _unknown7 = 0;
    int32_t _unknown8 = 0;
    int32_t _unknown9 = 0;
    int32_t _unknown10 = 0;
    int32_t _unknown11 = 0;
    int32_t _unknown12 = 0;
    int32_t _unknown13 = 0;
    int32_t _unknown14 = 0;
    int32_t _unknown15 = 0;
    int32_t _unknown16 = 0;

    Type _type;
};

}
}
}
#endif // FALLTERGEIST_FORMAT_MAP_SCRIPT_H
