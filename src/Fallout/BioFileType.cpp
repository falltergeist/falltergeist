#include "../Fallout/BioFileType.h"
#include "../Fallout/DatFileItem.h"

#include <iostream>

namespace Falltergeist
{

BioFileType::BioFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _text = 0;
    _init();
}

BioFileType::~BioFileType()
{
    delete [] _text;
}

void BioFileType::_init()
{
    _text = new char[_datFileItem->size() + 1]();
    for (unsigned int i = 0; i != _datFileItem->size(); ++i)
    {
        _text[i] = _datFileItem->getData()[i];
    }
}

char * BioFileType::getText()
{
    return _text;
}

}
