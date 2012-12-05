#include "../Fallout/AafFileType.h"

namespace Falltergeist
{

AafFileType::AafFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _init();
}

AafFileType::~AafFileType()
{
    delete [] _glyphs; _glyphs = 0;
}

void AafFileType::_init()
{
    setPosition(0);
    // signature
    skipBytes(4);
    (*this) >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;
    _glyphs = new AafGlyph[256];

    for (int i = 0; i != 256; ++i)
    {
        (*this) >> _glyphs[i].width >> _glyphs[i].height >> _glyphs[i].dataOffset;
    }

    setPosition(0x080C);
    for (int i = 0; i != 256; ++i)
    {
        unsigned int width = _glyphs[i].width;
        unsigned int height = _glyphs[i].height;
        if ( width * height  == 0) continue;

        _glyphs[i].data = new char[width * height];

        readBytes(_glyphs[i].data, width*height);
    }
}

AafGlyph * AafFileType::getChar(unsigned char chr)
{
    return &_glyphs[chr];
}

unsigned short AafFileType::getHorizontalGap()
{
    return _horizontalGap;
}

unsigned short AafFileType::getSpaceWidth()
{
    return _spaceWidth;
}

unsigned short AafFileType::getMaximumHeight()
{
    return _maximumHeight;
}

}
