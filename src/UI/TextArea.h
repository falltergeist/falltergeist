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
    TextArea(const Point& pos = Point());
    TextArea(int x = 0, int y = 0);
    TextArea(const std::string& text, const Point& pos = Point());
    TextArea(const std::string& text, int x, int y);
    TextArea(const TextArea& textArea, Point pos = Point());
    ~TextArea() override;

    std::string text() const;
    void setText(const std::string& text);
    void appendText(const std::string& text);

    HorizontalAlign horizontalAlign() const;
    void setHorizontalAlign(HorizontalAlign align);

    VerticalAlign verticalAlign() const;
    void setVerticalAlign(VerticalAlign align);

    Size size() const override;
    void setSize(const Size& size);

    void setWidth(int width);

    bool wordWrap() const;
    void setWordWrap(bool wordWrap);

    std::shared_ptr<Font> font();
    void setFont(std::shared_ptr<Font> font);

    void render(bool eggTransparency = false) override;
    unsigned int pixel(const Point& pos) override;

    unsigned int timestampCreated();

    TextArea& operator<<(const std::string& text);
    TextArea& operator<<(unsigned value);
    TextArea& operator<<(signed value);

    TextArea& operator+=(const std::string& text);
    TextArea& operator+=(unsigned value);
    TextArea& operator+=(signed value);

    TextArea& operator=(const std::string& text);
    TextArea& operator=(unsigned value);
    TextArea& operator=(signed value);

protected:
    bool _changed = true;
    std::vector<TextSymbol> _symbols;
    std::string _text;
    std::shared_ptr<Font> _font;

    HorizontalAlign _horizontalAlign = HorizontalAlign::LEFT;
    VerticalAlign _verticalAlign = VerticalAlign::TOP;

    Size _size;

    // not used when _width || _height are set manualy
    Size _calculatedSize;

    unsigned int _backgroundColor = 0;
    bool _wordWrap = false;
    unsigned int _outlineColor = 0;
    unsigned int _timestampCreated = 0;

    void _calculate();

};

}
}
#endif // FALLTERGEIST_UI_TEXTAREA_H
