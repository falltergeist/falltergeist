#include "../Fallout/BioFileType.h"

#include <iostream>

namespace Falltergeist
{

BioFileType::BioFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _init();
}

BioFileType::~BioFileType()
{
}

void BioFileType::_init()
{    
    (*this) << (unsigned char) 0;
}

char * BioFileType::getText()
{
    return getData();
}

}
