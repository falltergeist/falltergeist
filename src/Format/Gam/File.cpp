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
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

// Falltergeist includes
#include "../../Format/Gam/File.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Gam
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    unsigned int i = 0;
    unsigned char ch;
    std::string line;
    while (i != this->size())
    {
        *this >> ch; i++;
        if (ch != 0x0D) // \r
        {
            line += ch;
        }
        else
        {
            this->skipBytes(1); i++;// 0x0A \n
            _parseLine(line);
            line.clear();
        }
    }
    if (line.length() != 0)
    {
        _parseLine(line);
    }

}

void File::_parseLine(std::string line)
{
    // отрезаем всё что после комментариев
    if(line.find("//") != std::string::npos)
    {
        line = line.substr(0, line.find("//"));
    }

    // rtrim
    line.erase(std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());

    if (line.length() == 0) return;

    if (line == "GAME_GLOBAL_VARS:")
    {
        _GVARmode = true;
        return;
    }
    if (line == "MAP_GLOBAL_VARS:")
    {
        _MVARmode = true;
        return;
    }

    std::string name = line.substr(0, line.find(":="));
    std::string value = line.substr(line.find(":=")+2,line.find(";")-line.find(":=")-2);
    // rtrim
    name.erase(std::find_if(name.rbegin(), name.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), name.end());

    if (_GVARmode)
    {
        _GVARS.insert(std::make_pair(name, std::stoi(value)));
        return;
    }
    else if(_MVARmode)
    {
        _MVARS.insert(std::make_pair(name, std::stoi(value)));
        return;
    }
    else
    {
        throw Exception("File::_initialize() - unknown mode");
    }
}

std::map<std::string, int>* File::GVARS()
{
    _initialize();
    return &_GVARS;
}

std::map<std::string, int>* File::MVARS()
{
    _initialize();
    return &_MVARS;
}

int File::GVAR(std::string name)
{
    if (_GVARS.find(name) != _GVARS.end())
    {
        return _GVARS.at(name);
    }
    throw Exception("File::GVAR(name) - GVAR not found:" + name);
}

int File::MVAR(std::string name)
{
    if (_MVARS.find(name) != _MVARS.end())
    {
        return _MVARS.at(name);
    }
    throw Exception("File::MVAR(name) - MVAR not found:" + name);
}

int File::GVAR(unsigned int number)
{
    unsigned int i = 0;
    for (auto gvar : _GVARS)
    {
        if (i == number) return gvar.second;
        i++;
    }
    throw Exception("File::GVAR(number) - not found: " + std::to_string(number));
}

int File::MVAR(unsigned int number)
{
    unsigned int i = 0;
    for (auto mvar : _MVARS)
    {
        if (i == number) return mvar.second;
        i++;
    }
    throw Exception("File::MVAR(number) - not found: " + std::to_string(number));
}

}
}
}
