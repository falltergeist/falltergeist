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

#ifndef FALLTERGEIST_UI_MULTISTATEIMAGEBUTTON_H
#define	FALLTERGEIST_UI_MULTISTATEIMAGEBUTTON_H

// C++ standard includes
#include <string>
#include <vector>

// Falltergeist includes
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"
#include "../UI/ImageList.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Mouse;
}
namespace UI
{

class ImageList;
class Image;

class MultistateImageButton : public Falltergeist::UI::Base
{
public:
    enum class Mode
    {
        PROGRESSION = 1,
        CYCLIC
    };
    enum class Type
    {
        BIG_SWITCH = 1,
        SMALL_SWITCH
    };
    MultistateImageButton(const Point& pos);
    MultistateImageButton(Type type, int x, int y);
    ~MultistateImageButton() override;

    unsigned int state() const;
    void setState(unsigned int state);

    unsigned int minState() const;
    void setMinState(unsigned int value);

    unsigned int maxState() const;
    void setMaxState(unsigned int value);

    Mode mode() const;
    void setMode(Mode mode);

    int modeFactor() const;
    void setModeFactor(int factor);

    virtual void handle(Event::Mouse* mouseEvent) override;


    virtual bool opaque(const Point &pos) override;

    virtual void render(bool eggTransparency) override;


    virtual Size size() const override;

protected:
    std::shared_ptr<Graphics::Sprite> _sprite;
    std::vector<SDL_Rect> _rects;
    unsigned int _currentState = 0;
    Mode _mode = Mode::CYCLIC;
    Size _size;
    int _modeFactor = 1; // or -1
    unsigned int _maxState = 0;
    unsigned int _minState = 0;
    std::string _downSound;
    std::string _upSound;
    
    void _onMouseClick(Event::Mouse* event);
    void _onMouseUp(Event::Mouse* event);

};

}
}
#endif	// FALLTERGEIST_UI_MULTISTATEIMAGEBUTTON_H

