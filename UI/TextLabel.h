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
    unsigned int _color;
    unsigned int _width;
    unsigned int _height;
    unsigned int _horizontalAlign;
    unsigned int _verticalAlign;
    const char * _label;
    Font * _font;
public:
    enum { HORIZONTAL_ALIGN_LEFT = 0, HORIZONTAL_ALIGN_CENTER, HORIZONTAL_ALIGN_RIGHT, HORIZONTAL_ALIGN_JUSTIFY };
    enum { VERTICAL_ALIGN_TOP = 0, VERTIVAL_ALIGN_CENTER, VERTICAL_ALIGN_BOTTOM, VERTICAL_ALIGN_JUSTIFY };
    TextLabel(const char * label, int x = 0, int y = 0);
    ~TextLabel();
    Font * getFont();
    void setColor(unsigned int color);
    void setFont(const char * filename);
    void setHeight(unsigned int height);
    void setWidth(unsigned int width);
    void setHorizontalAlign(unsigned int align);
    void setVerticalAlign(unsigned int align);
    virtual void draw();
    unsigned int getHeight();
    unsigned int getWidth();
    unsigned int getHorizontalAlign();
    unsigned int getVerticalAlign();

};

}
#endif // FALLTERGEIST_TEXTLABEL_H
