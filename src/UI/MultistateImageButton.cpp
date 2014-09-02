/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// C++ standard includes

// Falltergeist includes
#include "../UI/MultistateImageButton.h"
#include "../Engine/Exception.h"
#include "../Engine/ActiveUI.h"
#include "../UI/Image.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

MultistateImageButton::MultistateImageButton(int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MultistateImageButton::_onLeftButtonClick);
}

MultistateImageButton::MultistateImageButton(unsigned int type, int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MultistateImageButton::_onLeftButtonClick);
    Image* image;
    switch (type)
    {
        case TYPE_BIG_SWITCH:
        {
            auto image = new Image("art/intrface/prfbknbs.frm");

            auto image1 = new Image(46, 47);
            image->texture()->copyTo(image1->texture(), 0, 0, 0, 0*47, 46, 47);
            auto image2 = new Image(46, 47);
            image->texture()->copyTo(image2->texture(), 0, 0, 0, 1*47, 46, 47);
            auto image3 = new Image(46, 47);
            image->texture()->copyTo(image3->texture(), 0, 0, 0, 2*47, 46, 47);
            auto image4 = new Image(46, 47);
            image->texture()->copyTo(image4->texture(), 0, 0, 0, 3*47, 46, 47);

            addImage(image1);
            addImage(image2);
            addImage(image3);
            addImage(image4);
            delete image1;
            delete image2;
            delete image3;
            delete image4;
            delete image;
            break;
        }
        case TYPE_SMALL_SWITCH:
        {
            auto image = new Image("art/intrface/prflknbs.frm");
            auto image1 = new Image(22, 25);
            auto image2 = new Image(22, 50);
            image->texture()->copyTo(image1->texture(), 0, 0, 0, 0, 22, 25);
            image->texture()->copyTo(image2->texture(), 0, 0, 0, 25, 22, 50);
            delete image1;
            delete image2;
            delete image;
            break;
        }
        default:
            throw Exception("MultistateImageButton::MultistateImageButton(unsigned int type, x, y) - unsupported type");
    }
}


MultistateImageButton::MultistateImageButton(ImageList imageList, int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MultistateImageButton::_onLeftButtonClick);
    for (auto image: *imageList.images()) _imageList.addImage(new Image(image));
}

MultistateImageButton::MultistateImageButton(ImageList* imageList, int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MultistateImageButton::_onLeftButtonClick);
    for (auto image: *imageList->images()) _imageList.addImage(new Image(image));
}


MultistateImageButton::~MultistateImageButton()
{
}

void MultistateImageButton::addImage(Image* image)
{
    _imageList.addImage(new Image(image));
    _maxState++;
}

unsigned int MultistateImageButton::state()
{
    return _currentState;
}

void MultistateImageButton::setState(unsigned int state)
{
    _currentState = state;
}

void MultistateImageButton::setMode(int mode)
{
    switch(mode)
    {
        case MODE_CYCLIC:
        case MODE_PROGRESSION:
                break;
        default:
            throw Exception("MultistateImageButton::setMode(int) - wrong mode number: " + std::to_string(mode));
    }
    _mode = mode;    
}

int MultistateImageButton::mode()
{
    return _mode;
}

void MultistateImageButton::_onLeftButtonClick(MouseEvent* event)
{
    if (mode() == MODE_PROGRESSION)
    {
        if (modeFactor() > 0)
        {
            _currentState = (_currentState < _maxState - 1) ? _currentState + modeFactor() : 0;
        }
        else
        {
            _currentState = (_currentState > 0) ? _currentState + modeFactor() : _maxState - 1;
        }
    }        
    else // MODE_CYCLIC
    {
        if (modeFactor() > 0)
        {
            if (_currentState == _maxState - 1) setModeFactor(-modeFactor());
        }
        else
        {
            if (_currentState == 0) setModeFactor(-modeFactor());
        }
        _currentState += modeFactor();
    }
}

Texture* MultistateImageButton::texture()
{
    return _imageList.images()->at(_currentState)->texture();
}

void MultistateImageButton::setModeFactor(int factor)
{
    _modeFactor = factor;
}

int MultistateImageButton::modeFactor()
{
    if (_modeFactor >= 0) return 1;
    return -1;
}

void MultistateImageButton::setMaxState(unsigned int value)
{
    _maxState = value;
    if (_currentState > _maxState) _currentState = _maxState;
}

unsigned int MultistateImageButton::maxState()
{
    return _maxState;
}

void MultistateImageButton::setMinState(unsigned int value)
{
    _minState = value;
    if (_currentState < _minState) _currentState = _minState;
}

unsigned int MultistateImageButton::minState()
{
    return _minState;
}


}
