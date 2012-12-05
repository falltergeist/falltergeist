#ifndef FALLTERGEIST_FONFILETYPE_H
#define FALLTERGEIST_FONFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

struct FonSymbol
{
    unsigned int width;
    unsigned int dataOffset;
    char * data;
};

class FonFileType : public VirtualFile
{
protected:
    void _init();
    unsigned int _numberOfCharacters;
    unsigned int _height;
    unsigned int _distance;
    FonSymbol * _symbols;
public:
    FonFileType(VirtualFile * virtualFile);
    ~FonFileType();
};

}
#endif // FALLTERGEIST_FONFILETYPE_H
