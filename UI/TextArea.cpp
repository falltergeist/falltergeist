#include "UI/TextArea.h"
#include "Engine/Font.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

namespace Falltergeist
{

TextArea::TextArea(const char * text, int x, int y) : InteractiveSurface(0,0,x,y)
{
    _text = 0;
    this->setText(text);
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _color = 0x00FF00FF;
    _font = new Font("font1.aaf", _color);
}

TextArea::TextArea(int x, int y) : InteractiveSurface(0,0,x,y)
{
    _text = 0;
    this->setText(" ");
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _color = 0x00FF00FF;
    _font = new Font("font1.aaf", _color);
}


TextArea::~TextArea()
{
    if (_text != 0) delete [] _text;
    delete _font; _font = 0;
}

void TextArea::draw()
{
    if (!needRedraw) return;
    
    if (_font == 0) throw Exception("TextArea::draw() - font is not setted");
    if (_text == 0 || strlen(_text) == 0) throw Exception("TextArea::draw() - text is 0");

    std::vector<std::string *> * lines = new std::vector<std::string *>;
    std::vector<Surface *> * linesSurfaces = new std::vector<Surface *>;

    unsigned int width = 0;
    unsigned int maxWidth = 0;
    unsigned int height = _font->getHeight();
    unsigned int i = 0;
    int x = 0;
    int y = 0;

    //calculating size of text surface
    int lineCount = 0;
    lines->push_back(new std::string(""));
    //*line = ;
    //std::cout << i << std::endl;
    while (_text[i] != 0)
    {
        if (_text[i] == 0x0A || _text[i] == '\n')
        {
            lineCount++;
            if (width > maxWidth) maxWidth = width;
            width = 0;
            lines->push_back(new std::string(""));
            //i++;
        }
        else
        {
            lines->at(lineCount)->push_back(_text[i]);
            width += _font->getGlyph(_text[i])->getWidth();
            width += _font->getHorizontalGap();
        }
        i++;
    }
    if (width <= maxWidth) width = maxWidth;
    height = (_font->getHeight() * lines->size()) + (_font->getHorizontalGap() * (lines->size() - 1));

    // foreach text line
    for (std::vector<std::string *>::iterator it = lines->begin(); it != lines->end(); ++it)
    {
        int lineWidth = 0;
        x = 0;
        for(i = 0; i != (*it)->size(); ++i)
        {
            lineWidth += _font->getGlyph((*it)->c_str()[i])->getWidth();
            if (i < (*it)->size() - 1) lineWidth += _font->getHorizontalGap();
        }

        //std::cout << lineWidth << ":" << _font->getHeight() << std::endl;
        Surface * lineSurface = new Surface(lineWidth, _font->getHeight());
        for(i = 0; i != (*it)->size(); ++i)
        {
            Surface * glyph = _font->getGlyph((*it)->c_str()[i]);
            glyph->setX(x);
            glyph->blit(lineSurface);

            x += glyph->getWidth();
            if (i < (*it)->size() - 1) x += _font->getHorizontalGap();
        }
        linesSurfaces->push_back(lineSurface);
    }
    // Creating new textSurface
    Surface * textSurface = new Surface(width,height);
    // foreach lines surfaces
    x = 0;
    y = 0;
    for (std::vector<Surface *>::iterator it = linesSurfaces->begin(); it != linesSurfaces->end(); ++it)
    {
        switch(_horizontalAlign)
        {
            case HORIZONTAL_ALIGN_LEFT:
                break;
            case HORIZONTAL_ALIGN_CENTER:
            x = (width-(*it)->getWidth())/2;
                break;
            case HORIZONTAL_ALIGN_RIGHT:
                x = width - (*it)->getWidth();
                break;
            case HORIZONTAL_ALIGN_JUSTIFY:
                //@todo justify
                break;
        }
        (*it)->setX(x);
        (*it)->setY(y);
        (*it)->blit(textSurface);
        //delete(*it);
        y += _font->getHeight() + _font->getVerticalGap();
    }
    delete linesSurfaces;

    if (_width == 0 && _height == 0)
    {
        textSurface->setX(getX());
        textSurface->setY(getY());
        loadFromSurface(textSurface);
        delete lines;
        InteractiveSurface::draw();
        return;
    }

    if (_height == 0) _height = height;

    // using align
    Surface * surface = new Surface(_width,_height,getX(),getY());
    x = 0; y = 0;
    switch(_horizontalAlign)
    {
        case HORIZONTAL_ALIGN_LEFT:
            break;
        case HORIZONTAL_ALIGN_CENTER:
        x = (_width-textSurface->getWidth())/2;
            break;
        case HORIZONTAL_ALIGN_RIGHT:
            x = _width - textSurface->getWidth();
            break;
        case HORIZONTAL_ALIGN_JUSTIFY:
            //@todo justify
            break;
    }
    switch(_verticalAlign)
    {
        case VERTICAL_ALIGN_TOP:
            break;
        case VERTICAL_ALIGN_CENTER:
        case VERTICAL_ALIGN_JUSTIFY:
            y = (_height - height)/2 ;
            break;
        case VERTICAL_ALIGN_BOTTOM:
            y = _height - height;
            break;
    }
    textSurface->setX(x);
    textSurface->setY(y);
    textSurface->blit(surface);
    loadFromSurface(surface);
    delete lines;
    delete textSurface;
    InteractiveSurface::draw();

}

unsigned int TextArea::getColor()
{
    return _color;
}

void TextArea::setColor(unsigned int color)
{
    if (_color == color) return;
    _color = color;
    if (!_font) return;
    _font->setColor(color);
    needRedraw = true;
}

unsigned int TextArea::getHeight()
{
    return _height;
}

void TextArea::setHeight(unsigned int height)
{
    if (height == _height) return;
    _height = height;
    needRedraw = true;
}

unsigned int TextArea::getWidth()
{
    return _width;
}

void TextArea::setWidth(unsigned int width)
{
    if (_width == width) return;
    _width = width;
    needRedraw = true;
}

unsigned char TextArea::getHorizontalAlign()
{
    return _horizontalAlign;
}

void TextArea::setHorizontalAlign(unsigned char align)
{
    if (_horizontalAlign == align) return;
    _horizontalAlign = align;
    needRedraw = true;
}

unsigned char TextArea::getVerticalAlign()
{
    return _verticalAlign;
}

void TextArea::setVerticalAlign(unsigned char align)
{
    if (_verticalAlign == align) return;
    _verticalAlign = align;
    needRedraw = true;
}

char * TextArea::getText()
{
    return _text;
}

void TextArea::setText(unsigned int number)
{
    std::stringstream ss;
    ss << number;
    setText(ss.str().c_str());

}

void TextArea::setText(const char * text)
{
    if (text == 0) 
    {
        delete [] _text;
        _text = 0;
        return;
    }
    _text = new char[strlen(text)+1]();
    for (unsigned int i = 0; i != strlen(text); ++i)
    {
        _text[i] = text[i];
    }
    //strcpy(_text,text);
    needRedraw = true;
}

void TextArea::setFont(const char * filename)
{
    delete _font; _font = 0;
    _font = new Font(filename, _color);
    needRedraw = true;
}

}
