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
