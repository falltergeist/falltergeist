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

#ifndef FALLTERGEIST_FORMAT_TXT_CSVPARSER_H
#define FALLTERGEIST_FORMAT_TXT_CSVPARSER_H

// C++ standard includes
#include <list>
#include <memory>
#include <string>
#include <vector>

// Falltergeist includes
#include "../Ini/Value.h"
#include "../Txt/Parser.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Txt
{

typedef std::list<std::vector<Ini::Value>> CSVFile;

/**
 * @brief Parser of CSV files.
 */
class CSVParser : public Parser
{
public:
    CSVParser(std::istream &stream);
    ~CSVParser();

    std::unique_ptr<CSVFile> parse();

private:
    std::istream &_stream; // stream to parse

protected:

    void _stripComments(std::string& line);

};

}
}
}
#endif // FALLTERGEIST_FORMAT_TXT_CSVPARSER_H
