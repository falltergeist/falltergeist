#ifndef FALLTERGEIST_AAFFILETYPE_H
#define FALLTERGEIST_AAFFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{
struct AafGlyph
{
    unsigned short width;
    unsigned short height;
    unsigned int dataOffset;
    char * data;
};

class AafFileType : public VirtualFile
{
protected:
    unsigned short _maximumHeight;
    unsigned short _horizontalGap;
    unsigned short _spaceWidth;
    unsigned short _verticalGap;
    AafGlyph * _glyphs;
    void _init();
public:
    AafFileType(VirtualFile * virtualFile);
    AafGlyph * getChar(unsigned char chr);
    unsigned short getSpaceWidth();
    unsigned short getHorizontalGap();
    unsigned short getMaximumHeight();
    ~AafFileType();
};

}
#endif // FALLTERGEIST_AAFFILETYPE_H
