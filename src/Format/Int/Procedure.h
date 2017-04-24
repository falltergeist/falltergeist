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

#ifndef FALLTERGEIST_FORMAT_INT_PROCEDURE_H
#define FALLTERGEIST_FORMAT_INT_PROCEDURE_H

// C++ standard includes
#include <cstdint>
#include <string>

// Falltergeist includes
#include "../../Format/Enums.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Int
{

class Procedure
{

public:
    Procedure();

    uint32_t flags() const;
    void setFlags(uint32_t flags);

    uint32_t delay() const;
    void setDelay(uint32_t delay);

    uint32_t conditionOffset() const;
    void setConditionOffset(uint32_t offset);

    uint32_t bodyOffset() const;
    void setBodyOffset(uint32_t offset);

    uint32_t argumentsCounter();
    void setArgumentsCounter(uint32_t value);

    std::string name() const;
    void setName(const std::string& name);

    bool isTimed();
    bool isConditional();
    bool isImported();
    bool isExported();
    bool isCritical();
    bool isPure();
    bool isInline();

protected:
    std::string _name;
    uint32_t _flags = 0;
    uint32_t _delay = 0; // delay for timed procedures
    uint32_t _conditionOffset = 0; // offset of condition in code for conditional procedures
    uint32_t _bodyOffset = 0; // procedure body offset from the beginning of the file
    uint32_t _argumentsCounter = 0; // number of arguments

};

}
}
}
#endif // FALLTERGEIST_FORMAT_INT_PROCEDURE_H
