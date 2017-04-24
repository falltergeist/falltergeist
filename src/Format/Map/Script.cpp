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

// Falltergeist includes
#include "../Map/Script.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Map
{

int32_t Script::PID() const
{
    return _PID;
}

void Script::setPID(int32_t PID)
{
    _PID = PID;
}

int32_t Script::scriptId() const
{
    return _scriptId;
}

void Script::setScriptId(int32_t value)
{
    _scriptId = value;
}

Script::Type Script::type() const
{
    return _type;
}

void Script::setType(Script::Type type)
{
    _type = type;
}

void Script::setSpatialTile(uint32_t tile)
{
    _spatialTile = tile;
}

uint32_t Script::spatialTile() const
{
    return _spatialTile;
}

void Script::setSpatialRadius(uint32_t radius)
{
    _spatialRadius = radius;
}

uint32_t Script::spatialRadius() const
{
    return _spatialRadius;
}

void Script::setTimerTime(uint32_t time)
{
    _timerTime = time;
}

uint32_t Script::timerTime() const
{
    return _timerTime;
}
}
}
}
