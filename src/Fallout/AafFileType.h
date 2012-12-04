#ifndef FALLTERGEIST_AAFFILETYPE_H
#define FALLTERGEIST_AAFFILETYPE_H

namespace Falltergeist
{
class DatFileItem;

struct AafGlyph
{
    unsigned short width;
    unsigned short height;
    unsigned int dataOffset;
    char * data;
};

class AafFileType
{
protected:
    unsigned short _maximumHeight;
    unsigned short _horizontalGap;
    unsigned short _spaceWidth;
    unsigned short _verticalGap;
    AafGlyph * _glyphs;
    DatFileItem * _datFileItem;
    void _init();
public:
    AafFileType(DatFileItem * datFileItem);
    AafGlyph * getChar(unsigned char chr);
    unsigned short getSpaceWidth();
    unsigned short getHorizontalGap();
    unsigned short getMaximumHeight();
    ~AafFileType();
};

}
#endif // FALLTERGEIST_AAFFILETYPE_H
