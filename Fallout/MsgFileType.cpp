#include "Fallout/MsgFileType.h"
#include "Fallout/DatFileItem.h"
#include <cstring>
#include <string>
#include <stdlib.h>

#include <iostream>

namespace Falltergeist
{


MsgFileType::MsgFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _lines = new std::vector<MsgLine *>;
    _init();
}

void MsgFileType::_init()
{
    _datFileItem->seek(0);
    unsigned int i = 0;
    unsigned char chr;
    while (i < _datFileItem->size())
    {
        chr = _datFileItem->getData()[i];
        // = 0;
        std::string line = "";
        while (chr != 0x0D)
        {
            chr = _datFileItem->getData()[i];
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
