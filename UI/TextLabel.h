#ifndef FALLTERGEIST_TEXTLABEL_H
#define FALLTERGEIST_TEXTLABEL_H

#include "InteractiveSurface.h"
#include "Font.h"

namespace Falltergeist
{
class AafFileType;

class TextLabel : public InteractiveSurface
{
protected:
    unsigned int _width;
    unsigned int _height;
    const char * _label;
    Font * _font;
    Surface * _generateSurface();
public:
    TextLabel(const char * label, const char * filename, int x = 0, int y = 0);
    ~TextLabel();
    Font * getFont();
    void setColor(unsigned int color);
};

}
#endif // FALLTERGEIST_TEXTLABEL_H
