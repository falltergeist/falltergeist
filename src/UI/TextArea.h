/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_UI_TEXTAREA_H
#define FALLTERGEIST_UI_TEXTAREA_H

// C++ standard includes
#include <cstdint>
#include <string>
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
class Font;
class FontString;
class TextSymbol;

namespace UI
{

/**
 * Represents a block of text on screen.
 */
class TextArea : public Falltergeist::UI::Base
{
public:
    enum class HorizontalAlign : unsigned
    {
        LEFT = 1,
        CENTER,
        RIGHT,
        JUSTIFY
    };
    enum class VerticalAlign : unsigned
    {
        TOP = 1,
        CENTER,
        BOTTOM,
        JUSTIFY
    };
    /**
     * Creates empty TextArea at the given position.
     */
    TextArea(const Point& pos = Point());

    /**
     * Creates empty TextArea at the given position.
     */
    TextArea(int x = 0, int y = 0);

    /**
     * Creates TextArea with given text at the given position.
     */
    TextArea(const std::string& text, const Point& pos = Point());

    /**
     * Creates TextArea with given text at the given position.
     */
    TextArea(const std::string& text, int x, int y);

    /**
     * Creates TextArea as copy of another TextArea, placed at the given position (0,0 by default).
     */
    TextArea(const TextArea& textArea, Point pos = Point());
    ~TextArea() override;

    /**
     * Current text content.
     */
    std::string text() const;

    /**
     * Replaces text content. Line break character \n is used to span text to multiple lines.
     */
    void setText(const std::string& text);

    /**
     * Appends given string to existing text. Line break character \n is used to span text to multiple lines.
     */
    void appendText(const std::string& text);

    HorizontalAlign horizontalAlign() const;
    void setHorizontalAlign(HorizontalAlign align);

    VerticalAlign verticalAlign() const;
    void setVerticalAlign(VerticalAlign align);

    /**
     * Size of text area. It's either fixed value given to setSize() or previously calculated size.
     */
    Size size() const override;
    /**
     * Sets fixed size of TextArea. If this is not (0, 0) - calls to size() will always return this value,
     * regardless of actual width/height of TextArea on screen.
     * If wordWrap is also set to true, lines width will be limited to width provided.
     */
    void setSize(const Size& size);


    virtual void handle(Event::Event* event) override;

    /**
     * Size of actual text content of the text area.
     */
    Size textSize(); 
    
    /**
     * Number of actual lines of text as rendered.
     */
    int numLines();

    void setWidth(int width);

    /**
     * Whether Word Wrap is currently enabled or not.
     */
    bool wordWrap() const;

    /**
     * Enables or disabled Word Wrap for this control - automatic splitting of lines when they are longer then size().width().
     */
    void setWordWrap(bool wordWrap);

    /**
     * Whether text outline is currently enabled or not.
     */
    bool outline() const;

    /**
     * Enables or disables text outline. Default outline color is black.
     */
    void setOutline(bool outLine);

    /**
     * Current outline color.
     */
    unsigned int outlineColor() const;

    /**
     * Sets text outline color. 0 - disables outline, any other color will enable it.
     */
    void setOutlineColor(unsigned int color);

    Font* font();
    void setFont(Font* font);

    /**
     * Sets font by font filename and color.
     */
    void setFont(const std::string& fontName, unsigned int color);

    /**
     * Current font filename.
     */
    std::string fontName();

    void render(bool eggTransparency = false) override;
    unsigned int pixel(const Point& pos) override;

    unsigned int timestampCreated() const;

    /**
     * Appends given string to current text.
     */
    TextArea& operator<<(const std::string& text);
    /**
     * Appends string representation of given number.
     */
    TextArea& operator<<(unsigned value);
    /**
     * Appends string representation of given number.
     */
    TextArea& operator<<(signed value);

    /**
     * Appends given string to current text.
     */
    TextArea& operator+=(const std::string& text);
    /**
     * Appends string representation of given number.
     */
    TextArea& operator+=(unsigned value);
    /**
     * Appends string representation of given number.
     */
    TextArea& operator+=(signed value);

    /**
     * Replaces text content.
     */
    TextArea& operator=(const std::string& text);
    /**
     * Replaces content with string representation of given number.
     */
    TextArea& operator=(unsigned value);
    /**
     * Replaces content with string representation of given number.
     */
    TextArea& operator=(signed value);

protected:
    struct Line
    {
        // line width in pixels
        unsigned width = 0;
        std::vector<TextSymbol> symbols;
        
        bool operator < (const Line& rhs) 
        { 
            return width < rhs.width; 
        }
    };
    
    bool _changed = true;
    std::vector<TextSymbol> _symbols;
    std::string _text;
    Font* _font = nullptr;

    HorizontalAlign _horizontalAlign = HorizontalAlign::LEFT;
    VerticalAlign _verticalAlign = VerticalAlign::TOP;

    /**
     * User-defined size. 0 for each dimension represents "auto-size" for this dimension, so size() will return calculated size.
     */
    Size _size;

    /**
     * Real size of TextArea on screen, as determined by previous _calculate() call.
     */
    Size _calculatedSize;
    int _numLines;

    bool _wordWrap = false;

    // TODO: implement
    unsigned int _backgroundColor = 0;

    unsigned int _outlineColor = 0;
    unsigned int _timestampCreated = 0;

    void _calculate();
    
    virtual std::vector<Line> _generateLines();
    
    void _addOutlineSymbol(const TextSymbol& symb, Font* font, int32_t ofsX, int32_t ofsY);

};

}
}
#endif // FALLTERGEIST_UI_TEXTAREA_H
