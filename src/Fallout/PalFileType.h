#ifndef FALLTERGEIST_PALFILETYPE_H
#define FALLTERGEIST_PALFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

struct PalColor
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    operator int();
    operator unsigned int();
};

class PalFileType : public VirtualFile
{
protected:
    PalColor * _colors;
    void _init();
public:
    PalFileType(VirtualFile * virtualFile);
    ~PalFileType();
    PalColor * getColor(unsigned char colorIndex);
};

}
#endif // FALLTERGEIST_PALFILETYPE_H
