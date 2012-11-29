#ifndef FALLTERGEIST_TEXTAREA_H
#define FALLTERGEIST_TEXTAREA_H

#include "Engine/InteractiveSurface.h"

namespace Falltergeist
{
class Font;

class TextArea : public InteractiveSurface
{
protected:
    void _init();
    char * _text;
    unsigned char _horizontalAlign;
    unsigned char _verticalAlign;
    unsigned int _width;
    unsigned int _height;
    unsigned int _color;
    Font * _font;
public:
    enum { HORIZONTAL_ALIGN_LEFT = 0, HORIZONTAL_ALIGN_CENTER, HORIZONTAL_ALIGN_RIGHT, HORIZONTAL_ALIGN_JUSTIFY };
    enum { VERTICAL_ALIGN_TOP = 0, VERTICAL_ALIGN_CENTER, VERTICAL_ALIGN_BOTTOM, VERTICAL_ALIGN_JUSTIFY };
    TextArea(const char * text, int x = 0, int y = 0);
    TextArea(int x = 0, int y = 0);
    ~TextArea();
    void draw();
    char * getText();
    void setText(const char * text);
    void setText(unsigned int number);
    unsigned char getHorizontalAlign();
    void setHorizontalAlign(unsigned char align);
    unsigned char getVerticalAlign();
    void setVerticalAlign(unsigned char align);
    unsigned int getHeight();
    void setHeight(unsigned int height);
    unsigned int getWidth();
    void setWidth(unsigned int width);
    unsigned int getColor();
    void setColor(unsigned int color);
    void setFont(const char * filename);
};

}
#endif // FALLTERGEIST_TEXTAREA_H
