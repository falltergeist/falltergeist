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

#include "../Fallout/MsgFileType.h"
#include <cstring>
#include <string>
#include <stdlib.h>

#include <iostream>

namespace Falltergeist
{


MsgFileType::MsgFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _lines = new std::vector<MsgLine *>;
    _init();
}

void MsgFileType::_init()
{
    setPosition(0);
    unsigned int i = 0;
    unsigned char chr;
    while (i < getSize())
    {
        chr = getData()[i];
        // = 0;
        std::string line = "";
        while (chr != 0x0D)
        {
            chr = getData()[i];
            //std::cout << chr;
            if (chr != 0x0D && chr != 0x0A) line.push_back(chr);
            i++;

        }
        // \r\n
        i++;
        if (line.c_str()[0] == '{')
        {
            std::string code = "";
            std::string sound = "";
            std::string text = "";

            const char * data = line.c_str();
            unsigned int j = 1;
            while(j < line.length())
            {
                if (data[j] == '}') break;
                code.push_back(data[j]);
                j++;
            }
            j++; j++;
            while(j < line.length())
            {
                if (data[j] == '}') break;
                sound.push_back(data[j]);
                j++;
            }
            j++; j++;
            while(j < line.length())
            {
                if (data[j] == '}') break;
                text.push_back(data[j]);
                j++;
            }

            MsgLine * msgLine = new MsgLine;
            msgLine->code = atoi(code.c_str());

            msgLine->sound = new std::string(sound.c_str());
            msgLine->text = new std::string(text.c_str());

            _lines->push_back(msgLine);
        }
    }
}

const char * MsgFileType::getText(unsigned int number)
{
    std::vector<MsgLine *>::iterator it;
    for (it = _lines->begin(); it != _lines->end(); ++it)
    {
        if ((*it)->code == number) return (*it)->text->c_str();
    }
    return 0;
}

}
