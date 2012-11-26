#include "Fallout/FonFileType.h"
#include "Fallout/DatFileItem.h"

#include <iostream>

namespace Falltergeist
{

FonFileType::FonFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _init();
}

FonFileType::~FonFileType()
{

}

void FonFileType::_init()
{
    (*_datFileItem) >> _numberOfCharacters;
    std::cout << "number of characters: "  << _numberOfCharacters << std::endl;
    (*_datFileItem) >> _height;
    std::cout << "height" << _height << std::endl;
}

};
