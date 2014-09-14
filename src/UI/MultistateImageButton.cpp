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
#include <iostream>

// Falltergeist includes
#include "../Engine/ActiveUI.h"
#include "../Engine/Exception.h"
#include "../Engine/Graphics/Texture.h"
#include "../UI/Image.h"
#include "../UI/MultistateImageButton.h"

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
    //Image* image;
    switch (type)
    {
        case TYPE_BIG_SWITCH:
        {
            auto image = std::shared_ptr<Image>(new Image("art/intrface/prfbknbs.frm"));

            auto image1 = std::shared_ptr<Image>(new Image(46, 47));
            image->texture()->copyTo(image1->texture(), 0, 0, 0, 0*47, 46, 47);
            auto image2 = std::shared_ptr<Image>(new Image(46, 47));
            image->texture()->copyTo(image2->texture(), 0, 0, 0, 1*47, 46, 47);
            auto image3 = std::shared_ptr<Image>(new Image(46, 47));
            image->texture()->copyTo(image3->texture(), 0, 0, 0, 2*47, 46, 47);
            auto image4 = std::shared_ptr<Image>(new Image(46, 47));
            image->texture()->copyTo(image4->texture(), 0, 0, 0, 3*47, 46, 47);

            addImage(image1);
            addImage(image2);
            addImage(image3);
            addImage(image4);
            break;
        }
        case TYPE_SMALL_SWITCH:
        {
            auto image = std::shared_ptr<Image>(new Image("art/intrface/prflknbs.frm"));
            auto image1 = std::shared_ptr<Image>(new Image(22, 25));
            auto image2 = std::shared_ptr<Image>(new Image(22, 50));
            image->texture()->copyTo(image1->texture(), 0, 0, 0, 0, 22, 25);
            image->texture()->copyTo(image2->texture(), 0, 0, 0, 25, 22, 50);
            addImage(image1);
            addImage(image2);
            break;
        }
        default:
            throw Exception("MultistateImageButton::MultistateImageButton(unsigned int type, x, y) - unsupported type");
    }
}


MultistateImageButton::MultistateImageButton(std::shared_ptr<ImageList> imageList, int x, int y) : ActiveUI(x, y)
{
    addEventHandler("mouseleftclick", this, (EventRecieverMethod) &MultistateImageButton::_onLeftButtonClick);
    for (auto image: *imageList->images()) _imageList.addImage(image);
}


MultistateImageButton::~MultistateImageButton()
{
}

void MultistateImageButton::addImage(std::shared_ptr<Image> image)
{
    _imageList.addImage(image);
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

void MultistateImageButton::_onLeftButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto sender = dynamic_cast<MultistateImageButton*>(event->emitter());

    if (sender->mode() == MODE_PROGRESSION)
    {
        if (sender->modeFactor() > 0)
        {
            sender->_currentState = (sender->_currentState < sender->_maxState - 1) ? sender->_currentState + sender->modeFactor() : 0;
        }
        else
        {
            sender->_currentState = (sender->_currentState > 0) ? sender->_currentState + sender->modeFactor() : sender->_maxState - 1;
        }
    }        
    else // MODE_CYCLIC
    {
        if (sender->modeFactor() > 0)
        {
            if (sender->_currentState == sender->_maxState - 1) sender->setModeFactor(-sender->modeFactor());
        }
        else
        {
            if (sender->_currentState == 0) sender->setModeFactor(-sender->modeFactor());
        }
        sender->_currentState += sender->modeFactor();
    }
}

std::shared_ptr<Texture> MultistateImageButton::texture()
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
