/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../Fallout/LstFileType.h"

#include <iostream>

namespace Falltergeist
{

LstFileType::LstFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _strings = 0;
}

LstFileType::~LstFileType()
{
    delete _strings; _strings = 0;
}

std::list<std::string *> * LstFileType::getStrings()
{
    if (_strings) return _strings;

    _strings = new std::list<std::string *>;

    //read strings
    unsigned int i = 0;
    bool end = false;
    while (i < getSize())
    {
        std::string * line = new std::string();
        while ((getData()[i] != 0x0D) && (i < getSize()))
        {
            if (getData()[i] == 0x20) end = true;
            if (!end) line->push_back(getData()[i]);
            i++;
        }
        end = false;
        // skips \r\n
        i++; i++;
        _strings->push_back(line);
    }
    return _strings;
}


}
