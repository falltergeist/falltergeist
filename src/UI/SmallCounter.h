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

#ifndef FALLTERGEIST_SMALLCOUNTER_H
#define FALLTERGEIST_SMALLCOUNTER_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Graphics/ActiveUI.h"

// Third party includes

namespace Falltergeist
{
class Image;

class SmallCounter : public ActiveUI
{
public:
    enum class Color
    {
        WHITE = 1,
        YELLOW,
        RED
    };
    enum class Type
    {
        UNSIGNED = 0,
        SIGNED
    };

    SmallCounter(int x = 0, int y = 0);
    ~SmallCounter() override;

    Texture* texture() const override;

    void setColor(Color color);
    Color color();

    void setLength(unsigned int length);
    unsigned int length();

    void setNumber(signed int number);
    signed int number();

    void setType(Type type);
    Type type();

protected:
    Color _color = Color::WHITE;
    signed int _number = 0;
    unsigned int _length = 3;
    Type _type = Type::UNSIGNED;
    mutable std::unique_ptr<Texture> _textureOnDemand;

    void setTexture(Texture* texture) override;

private:
    // Hide unused field from childs.
    using ActiveUI::_texture;

    SmallCounter(const SmallCounter&) = delete;
    void operator=(const SmallCounter&) = delete;
    
};

}
#endif // FALLTERGEIST_SMALLCOUNTER_H
