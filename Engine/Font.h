#ifndef FALLTERGEIST_FONT_H
#define FALLTERGEIST_FONT_H

#include "Fallout/AafFileType.h"
#include "Engine/Surface.h"
#include <vector>

namespace Falltergeist
{

class Font
{
protected:
    std::vector<Surface *> * _glyphs;
    const char * _filename;
    unsigned int _color;
    AafFileType * _aafFileType;
public:
    Font(const char * filename, unsigned int color = 0x00FF00FF);
    ~Font();
    void setFilename(const char * filename);
    const char * getFilename();
    void setColor(unsigned int color);
    unsigned int getColor();
    Surface * getGlyph(unsigned char chr);
    unsigned short getHorizontalGap();
    unsigned short getVerticalGap();
    unsigned short getHeight();
};

}
#endif // FALLTERGEIST_FONT_H
