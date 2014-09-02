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
#include <iostream>

// Falltergeist includes
#include "../UI/ImageButton.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Exception.h"

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

void ImageButton::_onLeftButtonClick(MouseEvent* event)
{
    if (_checkboxMode)
    {
        _checked = _checked ? false : true;
    }
}

}
