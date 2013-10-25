/*
 * Copyright 2012-2013 Falltergeist Developers.
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
 *
 */

#ifndef FALLTERGEIST_SETTINGSMENUSTATE_H
#define	FALLTERGEIST_SETTINGSMENUSTATE_H

// C++ standard includes
#include <map>

// Falltergeist includes
#include "../Engine/State.h"
#include "../Engine/IniFile.h"

// Third party includes

namespace Falltergeist
{
class TextArea;
class InteractiveSurface;
    
class SettingsMenuState : public State
{
protected:
    InteractiveSurface * _fon;    
    std::map<std::string, TextArea*> _labels;
    IniFileSection _getDefaultSettings();
    IniFileSection _getSettings();
    TextArea* _addLabel(std::string name, TextArea* label);
public:
    SettingsMenuState(Game* game);
    virtual ~SettingsMenuState();
    virtual void init();
    virtual void think();
    void onDefaultButtonClick(Event* event);
    void onCancelButtonClick(Event* event);
    void onSaveButtonClick(Event* event);
    
    void onButtonPress(Event* event);
};

}
#endif	// FALLTERGEIST_SETTINGSMENUSTATE_H
