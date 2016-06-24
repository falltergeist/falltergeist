/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_UI_BIGCOUNTER_H
#define FALLTERGEIST_UI_BIGCOUNTER_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

class Image;

class BigCounter : public Falltergeist::UI::Base
{
public:
    enum class Color
    {
        WHITE = 1,
        RED
    };

    BigCounter(int x, int y, unsigned int length = 2);
    BigCounter(const Point& pos = Point(), unsigned int length = 2);
    ~BigCounter() override;

    void setColor(Color color);
    Color color();

    void setNumber(unsigned int number);
    unsigned int number();

protected:
    Color _color = Color::WHITE;
    unsigned int _number = 0;
    std::string _numberText = "";
    unsigned int _length = 2;
    std::shared_ptr<Graphics::Sprite> _sprite;
    std::vector<SDL_Rect> _rects;

public:
    virtual void render(bool eggTransparency) override;

    virtual bool opaque(const Point &pos) override;

private:

    BigCounter(const BigCounter&) = delete;
    void operator=(const BigCounter&) = delete;
};

}
}
#endif // FALLTERGEIST_UI_BIGCOUNTER_H
