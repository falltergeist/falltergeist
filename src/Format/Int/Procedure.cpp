/*
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

#include "../../Format/Int/Procedure.h"

namespace Falltergeist
{
namespace Format
{
namespace Int
{

Procedure::Procedure()
{
}

uint32_t Procedure::flags() const
{
    return _flags;
}

void Procedure::setFlags(uint32_t flags)
{
    _flags = flags;
}

uint32_t Procedure::delay() const
{
    return _delay;
}

void Procedure::setDelay(uint32_t delay)
{
    _delay = delay;
}

uint32_t Procedure::conditionOffset() const
{
    return _conditionOffset;
}

void Procedure::setConditionOffset(uint32_t offset)
{
    _conditionOffset = offset;
}

uint32_t Procedure::bodyOffset() const
{
    return _bodyOffset;
}

void Procedure::setBodyOffset(uint32_t offset)
{
    _bodyOffset = offset;
}

uint32_t Procedure::argumentsCounter()
{
    return _argumentsCounter;
}

void Procedure::setArgumentsCounter(uint32_t value)
{
    _argumentsCounter = value;
}

bool Procedure::isTimed()
{
    return flags() & (unsigned)PROCEDURE_FLAG::TIMED;
}

bool Procedure::isConditional()
{
    return flags() & (unsigned)PROCEDURE_FLAG::CONDITIONAL;
}

bool Procedure::isImported()
{
    return flags() & (unsigned)PROCEDURE_FLAG::IMPORTED;
}

bool Procedure::isExported()
{
    return flags() & (unsigned)PROCEDURE_FLAG::EXPORTED;
}

bool Procedure::isCritical()
{
    return flags() & (unsigned)PROCEDURE_FLAG::CRITICAL;
}

bool Procedure::isPure()
{
    return flags() & (unsigned)PROCEDURE_FLAG::PURE;
}

bool Procedure::isInline()
{
    return flags() & (unsigned)PROCEDURE_FLAG::INLINE;
}

std::string Procedure::name() const
{
    return _name;
}

void Procedure::setName(const std::string& name)
{
    _name = name;
}

}
}
}
