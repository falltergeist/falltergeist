#include "Fallout/BioFileType.h"
#include "Fallout/DatFileItem.h"
#include <string.h>

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
    delete _text;
}

void BioFileType::_init()
{
    //_text = new char[_datFileItem->size() + 1];
    _text = new std::string();
    for (unsigned int i = 0; i != _datFileItem->size(); ++i)
    {
        _text->push_back(_datFileItem->getData()[i]);
    }
    //_text[_datFileItem->size()] = 0;
}

const char * BioFileType::getText()
{
    return _text->c_str();
}

}
