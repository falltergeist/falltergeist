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

#ifndef FALLTERGEIST_SLIDER_H
#define FALLTERGEIST_SLIDER_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/ActiveUI.h"
#include "../UI/ImageList.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Event;
    class Mouse;
}

class Slider : public ActiveUI
{
protected:
    ImageList _imageList;
    double _minValue = 0.0;
    double _maxValue = 1.0;
    double _value = 0.0;
    void _onDrag(Event::Mouse* event);
    void _onLeftButtonDown(Event::Mouse* event);
    void _onLeftButtonUp(Event::Mouse* event);
public:
    Slider(int x, int y);
    virtual ~Slider();
    Texture* texture() const override;
    int x() const override;
    virtual void handle(Event::Event* event);
    double minValue();
    void setMinValue(double value);
    double maxValue();
    void setMaxValue(double value);
    double value();
    void setValue(double value);
};

}
#endif // FALLTERGEIST_SLIDER_H
