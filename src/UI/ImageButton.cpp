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
#include <string>

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/ResourceManager.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{

ImageButton::ImageButton(unsigned int type, int x, int y) : ActiveUI(x, y)
{
    switch (type)
    {
        case TYPE_SMALL_RED_CIRCLE:
            _textures.push_back(ResourceManager::texture("art/intrface/lilredup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/lilreddn.frm"));
            break;
        case TYPE_BIG_RED_CIRCLE:
            _textures.push_back(ResourceManager::texture("art/intrface/bigredup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/bigreddn.frm"));
            break;
        case TYPE_MENU_RED_CIRCLE:
            _textures.push_back(ResourceManager::texture("art/intrface/menuup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/menudown.frm"));
            break;
        case TYPE_SKILL_TOGGLE:
            _textures.push_back(ResourceManager::texture("art/intrface/tgskloff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/tgsklon.frm"));
            break;
        case TYPE_PLUS:
            _textures.push_back(ResourceManager::texture("art/intrface/splsoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/splson.frm"));
            break;
        case TYPE_MINUS:
            _textures.push_back(ResourceManager::texture("art/intrface/snegoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/snegon.frm"));
            break;
        case TYPE_LEFT_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/slu.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/sld.frm"));
            break;
        case TYPE_RIGHT_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/sru.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/srd.frm"));
            break;
        case TYPE_CHECKBOX:
            _textures.push_back(ResourceManager::texture("art/intrface/prfxout.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/prfxin.frm"));
            _checkboxMode = true;
            break;
        case TYPE_PLAYER_NAME:
            _textures.push_back(ResourceManager::texture("art/intrface/nameoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/nameon.frm"));
            break;
        case TYPE_PLAYER_AGE:
            _textures.push_back(ResourceManager::texture("art/intrface/ageoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/ageon.frm"));
            break;
        case TYPE_PLAYER_GENDER:
            _textures.push_back(ResourceManager::texture("art/intrface/sexoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/sexon.frm"));
            break;
        case TYPE_PANEL_INVENTORY:
            _textures.push_back(ResourceManager::texture("art/intrface/invbutup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/invbutdn.frm"));
            break;
        case TYPE_PANEL_OPTIONS:
            _textures.push_back(ResourceManager::texture("art/intrface/optiup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/optidn.frm"));
            break;
        case TYPE_PANEL_ATTACK:
            _textures.push_back(ResourceManager::texture("art/intrface/sattkbup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/sattkbdn.frm"));
            break;
        case TYPE_PANEL_MAP:
            _textures.push_back(ResourceManager::texture("art/intrface/mapup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/mapdn.frm"));
            break;
        case TYPE_PANEL_CHA:
            _textures.push_back(ResourceManager::texture("art/intrface/chaup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/chadn.frm"));
            break;
        case TYPE_PANEL_PIP:
            _textures.push_back(ResourceManager::texture("art/intrface/pipup.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/pipdn.frm"));
            break;
        case TYPE_OPTIONS_BUTTON:
            _textures.push_back(ResourceManager::texture("art/intrface/opbtnoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/opbtnon.frm"));
            break;
        case TYPE_SKILLDEX_BUTTON:
            _textures.push_back(ResourceManager::texture("art/intrface/skldxoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/skldxon.frm"));
            break;
        case TYPE_INVENTORY_UP_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/invupout.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/invupin.frm"));
            break;
        case TYPE_INVENTORY_DOWN_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/invdnout.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/invdnin.frm"));
            break;
        case TYPE_PIPBOY_ALARM_BUTTON:
            _textures.push_back(ResourceManager::texture("art/intrface/alarmout.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/alarmin.frm"));
            break;
        case TYPE_DIALOG_RED_BUTTON:
            _textures.push_back(ResourceManager::texture("art/intrface/di_rdbt1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_rdbt2.frm"));
            break;
        case TYPE_DIALOG_REVIEW_BUTTON:
            _textures.push_back(ResourceManager::texture("art/intrface/di_rest1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_rest2.frm"));
            break;
        case TYPE_DIALOG_DONE_BUTTON:
            _textures.push_back(ResourceManager::texture("art/intrface/di_done1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_done2.frm"));
            break;
        case TYPE_DIALOG_BIG_UP_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/di_bgup1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_bgup2.frm"));
            break;
        case TYPE_DIALOG_BIG_DOWN_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/di_bgdn1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_bgdn2.frm"));
            break;
        case TYPE_DIALOG_UP_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/di_up1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_up2.frm"));
            break;
        case TYPE_DIALOG_DOWN_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/di_down1.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/di_down2.frm"));
            break;
        case TYPE_SMALL_UP_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/uparwoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/uparwon.frm"));
            break;
        case TYPE_SMALL_DOWN_ARROW:
            _textures.push_back(ResourceManager::texture("art/intrface/dnarwoff.frm"));
            _textures.push_back(ResourceManager::texture("art/intrface/dnarwon.frm"));
            break;
        default:
            throw Exception("ImageButton::Imagebutton() - wrong button type");
    }
    addEventHandler("mouseleftclick", this, (EventRecieverMethod) &ImageButton::_onLeftButtonClick);
}

ImageButton::~ImageButton()
{
}

Texture* ImageButton::texture()
{
    if (_checkboxMode && _checked) return _textures.at(1);

    if (_hovered && _leftButtonPressed) return _textures.at(1);

    return _textures.at(0);
}

void ImageButton::_onLeftButtonClick(std::shared_ptr<MouseEvent> event)
{
    auto sender = dynamic_cast<ImageButton*>(event->emitter());
    if (sender->_checkboxMode)
    {
        sender->_checked = sender->_checked ? false : true;
    }
}

}
