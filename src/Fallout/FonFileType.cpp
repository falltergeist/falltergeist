#include "../Fallout/FonFileType.h"

#include <iostream>

namespace Falltergeist
{

FonFileType::FonFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _init();
}

FonFileType::~FonFileType()
{

}

void FonFileType::_init()
{
    (*this) >> _numberOfCharacters;
    //std::cout << "number of characters: "  << _numberOfCharacters << std::endl;
    (*this) >> _height;
    //std::cout << "height" << _height << std::endl;
}

};
