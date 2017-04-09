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

#ifndef FALLTERGEIST_FORMAT_INT_FILE_H
#define FALLTERGEIST_FORMAT_INT_FILE_H

// C++ standard includes
#include <map>
#include <string>
#include <vector>

// Falltergeist includes
#include "../../Format/Dat/Item.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Int/Procedure.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Int
{

class File : public Dat::Item
{
public:
    File(Dat::Stream&& stream);

    const std::vector<Procedure>& procedures() const;

    // returns procedure with a given name or nullptr if none found
    const Procedure* procedure(const std::string& name) const;

    const std::map<unsigned int, std::string>& identifiers() const;
    const std::map<unsigned int, std::string>& strings() const;

    // current position in script file
    size_t position() const;

    // set current position in script file
    void setPosition(size_t);

    // the size of script file
    size_t size() const;

    // read the next opcode
    uint16_t readOpcode();

    // read the next value
    uint32_t readValue();

protected:
    Dat::Stream _stream;

    std::vector<Procedure> _procedures;

    std::map<unsigned int, std::string> _functions;
    std::vector<unsigned int> _functionsOffsets;
    std::map<unsigned int, std::string> _identifiers;
    std::map<unsigned int, std::string> _strings;
};

}
}
}
#endif // FALLTERGEIST_FORMAT_INT_FILE_H
