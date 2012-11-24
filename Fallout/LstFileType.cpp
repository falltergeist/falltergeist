#include "LstFileType.h"
#include "DatFileItem.h"

#include <iostream>

namespace Falltergeist
{

LstFileType::LstFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
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
    while (i < _datFileItem->size())
    {
        std::string * line = new std::string();
        while ((_datFileItem->getData()[i] != 0x0D) && (i < _datFileItem->size()))
        {
            if (_datFileItem->getData()[i] == 0x20) end = true;
            if (!end) line->push_back(_datFileItem->getData()[i]);
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
