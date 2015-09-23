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

#ifndef FALLTERGEIST_UI_IMAGEBUTTON_H
#define FALLTERGEIST_UI_IMAGEBUTTON_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Mouse;
}
namespace UI
{

class ImageButton : public Falltergeist::UI::Base
{
public:
    enum class Type
    {
        SMALL_RED_CIRCLE = 1,
        BIG_RED_CIRCLE,
        MENU_RED_CIRCLE,
        SKILL_TOGGLE,
        PLUS,
        MINUS,
        LEFT_ARROW,
        RIGHT_ARROW,
        CHECKBOX,
        PLAYER_NAME,
        PLAYER_AGE,
        PLAYER_GENDER,
        PANEL_INVENTORY,
        PANEL_OPTIONS,
        PANEL_ATTACK,
        PANEL_MAP,
        PANEL_CHA,
        PANEL_PIP,
        OPTIONS_BUTTON,
        SKILLDEX_BUTTON,
        INVENTORY_UP_ARROW,
        INVENTORY_DOWN_ARROW,
        PIPBOY_ALARM_BUTTON,
        DIALOG_RED_BUTTON,
        DIALOG_REVIEW_BUTTON,
        DIALOG_DONE_BUTTON,
        DIALOG_BIG_UP_ARROW,
        DIALOG_BIG_DOWN_ARROW,
        DIALOG_UP_ARROW,
        DIALOG_DOWN_ARROW,
        SMALL_UP_ARROW,
        SMALL_DOWN_ARROW,
        MAP_HOTSPOT
    };
    ImageButton(Type type, Point pos = Point());
    ImageButton(Type type, int x, int y);
    ImageButton(const std::string& upImg, const std::string& downImg, const std::string& upSfx, const std::string& downSfx, int x, int y);
    ~ImageButton() override;

    //void setState(unsigned int value);
    Graphics::Texture* texture() const;

    bool checked();
    void setChecked(bool _checked);

protected:
    bool _checkboxMode = false; // remember new state after click
    bool _checked = false;

    std::vector<Graphics::Texture*> _textures;
    void _onLeftButtonClick(Event::Mouse* event);
    void _onLeftButtonDown(Event::Mouse* event);
    void _onMouseOut(Event::Mouse* event);
    void _initFromType(Type type);
    void _init();

};

}
}
#endif // FALLTERGEIST_UI_IMAGEBUTTON_H
