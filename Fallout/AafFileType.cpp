#include "Fallout/AafFileType.h"
#include "Fallout/DatFileItem.h"

namespace Falltergeist
{

AafFileType::AafFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _init();
}

AafFileType::~AafFileType()
{
    delete [] _glyphs; _glyphs = 0;
}

void AafFileType::_init()
{
    _datFileItem->seek(0);
    // signature
    _datFileItem->skip(4);
    (*_datFileItem) >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;
    _glyphs = new AafGlyph[256];

    for (int i = 0; i != 256; ++i)
    {
        (*_datFileItem) >> _glyphs[i].width >> _glyphs[i].height >> _glyphs[i].dataOffset;
    }

    for (int i = 0; i != 256; ++i)
    {
        unsigned int width = _glyphs[i].width;
        unsigned int height = _glyphs[i].height;
        if ( width * height  == 0) continue;

        _glyphs[i].data = new char[width * height];
        for (unsigned int j = 0; j != width*height; ++j)
        {
            _glyphs[i].data[j] = _datFileItem->getData()[0x080C + _glyphs[i].dataOffset + j];
        }
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
