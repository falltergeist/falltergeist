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

// Related headers
#include "../UI/ImageButton.h"

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../ResourceManager.h"

// Third party includes

namespace Falltergeist
{
using namespace std;

namespace UI
{


ImageButton::ImageButton(Type type, Point pos) : Base(pos)
{
    _init(type);
}

ImageButton::ImageButton(Type type, int x, int y) : ImageButton(type, Point(x, y))
{
}

ImageButton::~ImageButton()
{
}

void ImageButton::_init(Type type)
{
    switch(type)
    {
        case Type::SMALL_RED_CIRCLE:
            _butup = make_shared<Graphics::Sprite>("art/intrface/lilredup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/lilreddn.frm");

            _downSound = "sound/sfx/ib1p1xx1.acm";
            _upSound = "sound/sfx/ib1lu1x1.acm";
            break;
        case Type::BIG_RED_CIRCLE:
            _butup = make_shared<Graphics::Sprite>("art/intrface/bigredup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/bigreddn.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::MENU_RED_CIRCLE:
            _butup = make_shared<Graphics::Sprite>("art/intrface/menuup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/menudown.frm");
            _downSound = "sound/sfx/nmselec0.acm";
            _upSound = "sound/sfx/nmselec1.acm";
            break;
        case Type::SKILL_TOGGLE:
            _butup = make_shared<Graphics::Sprite>("art/intrface/tgskloff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/tgsklon.frm");
            break;
        case Type::PLUS:
            _butup = make_shared<Graphics::Sprite>("art/intrface/splsoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/splson.frm");
            break;
        case Type::MINUS:
            _butup = make_shared<Graphics::Sprite>("art/intrface/snegoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/snegon.frm");
            break;
        case Type::LEFT_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/slu.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/sld.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::RIGHT_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/sru.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/srd.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::CHECKBOX:
            _butup = make_shared<Graphics::Sprite>("art/intrface/prfxout.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/prfxin.frm");
            _upSound = "sound/sfx/ib2p1xx1.acm";
            _checkboxMode = true;
            break;
        case Type::PLAYER_NAME:
            _butup = make_shared<Graphics::Sprite>("art/intrface/nameoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/nameon.frm");
            break;
        case Type::PLAYER_AGE:
            _butup = make_shared<Graphics::Sprite>("art/intrface/ageoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/ageon.frm");
            break;
        case Type::PLAYER_GENDER:
            _butup = make_shared<Graphics::Sprite>("art/intrface/sexoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/sexon.frm");
            break;
        case Type::PANEL_INVENTORY:
            _butup = make_shared<Graphics::Sprite>("art/intrface/invbutup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/invbutdn.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::PANEL_OPTIONS:
            _butup = make_shared<Graphics::Sprite>("art/intrface/optiup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/optidn.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::PANEL_ATTACK:
            _butup = make_shared<Graphics::Sprite>("art/intrface/sattkbup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/sattkbdn.frm");
            _downSound = "sound/sfx/ib3p1xx1.acm";
            _upSound = "sound/sfx/ib3lu1x1.acm";
            break;
        case Type::PANEL_MAP:
            _butup = make_shared<Graphics::Sprite>("art/intrface/mapup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/mapdn.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::PANEL_CHA:
            _butup = make_shared<Graphics::Sprite>("art/intrface/chaup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/chadn.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::PANEL_PIP:
            _butup = make_shared<Graphics::Sprite>("art/intrface/pipup.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/pipdn.frm");
            _downSound = "sound/sfx/ib2p1xx1.acm";
            _upSound = "sound/sfx/ib2lu1x1.acm";
            break;
        case Type::OPTIONS_BUTTON:
            _butup = make_shared<Graphics::Sprite>("art/intrface/opbtnoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/opbtnon.frm");
            _downSound = "sound/sfx/ib3p1xx1.acm";
            _upSound = "sound/sfx/ib3lu1x1.acm";
            break;
        case Type::SKILLDEX_BUTTON:
            _butup = make_shared<Graphics::Sprite>("art/intrface/skldxoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/skldxon.frm");
            _downSound = "sound/sfx/ib2lu1x1.acm";
            _upSound = "sound/sfx/ib1p1xx1.acm";
            break;
        //TODO: add sound effects for inventory scroll buttons
        case Type::INVENTORY_UP_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/invupout.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/invupin.frm");
            break;
        case Type::INVENTORY_DOWN_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/invdnout.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/invdnin.frm");
            break;
        case Type::PIPBOY_ALARM_BUTTON:
            _butup = make_shared<Graphics::Sprite>("art/intrface/alarmout.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/alarmin.frm");
            break;
        case Type::DIALOG_RED_BUTTON:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_rdbt2.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_rdbt1.frm");
            break;
        case Type::DIALOG_REVIEW_BUTTON:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_rest1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_rest2.frm");
            break;
        case Type::DIALOG_DONE_BUTTON:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_done1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_done2.frm");
            break;
        case Type::DIALOG_BIG_UP_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_bgup1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_bgup2.frm");
            break;
        case Type::DIALOG_BIG_DOWN_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_bgdn1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_bgdn2.frm");
            break;
        case Type::DIALOG_UP_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_up1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_up2.frm");
            break;
        case Type::DIALOG_DOWN_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/di_down1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/di_down2.frm");
            break;
        case Type::SMALL_UP_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/uparwoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/uparwon.frm");
            break;
        case Type::SMALL_DOWN_ARROW:
            _butup = make_shared<Graphics::Sprite>("art/intrface/dnarwoff.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/dnarwon.frm");
            break;
        case Type::MAP_HOTSPOT:
            _butup = make_shared<Graphics::Sprite>("art/intrface/hotspot1.frm");
            _butdown = make_shared<Graphics::Sprite>("art/intrface/hotspot2.frm");
            break;
        default:
            throw Exception("ImageButton::Imagebutton() - wrong button type");
    }

    mouseClickHandler().add(std::bind(&ImageButton::_onMouseClick, this, std::placeholders::_1));
    mouseDownHandler().add(std::bind(&ImageButton::_onMouseDown, this, std::placeholders::_1));
    mouseOutHandler().add(std::bind(&ImageButton::_onMouseOut, this, std::placeholders::_1));
}

void ImageButton::_onMouseClick(Event::Mouse* event)
{
    if(!_enabled) return;
    auto sender = dynamic_cast<ImageButton*>(event->target());
    if (sender->_checkboxMode)
    {
        sender->_checked = !sender->_checked;
    }
    if (!sender->_upSound.empty())
    {
        Game::getInstance()->mixer()->playACMSound(sender->_upSound);
    }
}

void ImageButton::_onMouseDown(Event::Mouse* event)
{
    if (!event->leftButton() || !_enabled) return;

    auto sender = dynamic_cast<ImageButton*>(event->target());
    if (!sender->_downSound.empty())
    {
        Game::getInstance()->mixer()->playACMSound(sender->_downSound);
    }
}


void ImageButton::_onMouseOut(Event::Mouse* event)
{
//    if(!_enabled) return;
//    auto sender = dynamic_cast<ImageButton*>(event->target());
//    if (_leftButtonPressed && !sender->_upSound.empty())
//    {
//        Game::getInstance()->mixer()->playACMSound(sender->_upSound);
//    }
}


bool ImageButton::checked()
{
    return _checked;
}

void ImageButton::setChecked(bool _checked)
{
    this->_checked = _checked;
}

bool ImageButton::enabled()
{
    return _enabled;
}

void ImageButton::setEnabled(bool _enabled)
{
    this->_enabled = _enabled;
}

void ImageButton::handle(Event::Mouse* mouseEvent)
{
    if(!_enabled) return;
    // disable right button clicks
    _rightButtonPressed = false;
    Base::handle(mouseEvent);
}

void ImageButton::render(bool eggTransparency)
{
    if(!_enabled) return;
    if ((_checkboxMode && _checked) || (_leftButtonPressed))
    {
      _butdown->render(position().x(),position().y());
      return;
    }

    _butup->render(position().x(),position().y());

}


    bool ImageButton::opaque(const Point &pos) {
        return opaque(pos.x(),pos.y());
    }

    bool ImageButton::opaque(unsigned int x, unsigned int y) {
        if ((_checkboxMode && _checked) || (_hovered && _leftButtonPressed))
        {
            return _butdown->opaque(x,y);
        }

        return _butup->opaque(x,y);
    }
}
}
