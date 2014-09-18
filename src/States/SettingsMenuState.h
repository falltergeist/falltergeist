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
 *
 */

#ifndef FALLTERGEIST_SETTINGSMENUSTATE_H
#define FALLTERGEIST_SETTINGSMENUSTATE_H

// C++ standard includes
#include <map>

// Falltergeist includes
#include "../Engine/IniFile.h"
#include "../Engine/State.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{
class TextArea;
class InteractiveSurface;

class SettingsMenuState : public State
{
protected:
    std::map<std::string, std::shared_ptr<TextArea>> _labels;
    IniFileSection _getDefaultSettings();
    IniFileSection _getSettings();
    std::shared_ptr<TextArea> _addLabel(std::string name, std::shared_ptr<TextArea> label);
    std::shared_ptr<TextArea> _addTextArea(std::shared_ptr<libfalltergeist::MsgMessage> message, unsigned int x, unsigned int y);
    std::shared_ptr<TextArea> _addTextArea(std::shared_ptr<TextArea> parent, unsigned int x, unsigned int y);
public:
    SettingsMenuState();
    virtual ~SettingsMenuState();
    virtual void init();
    virtual void think();

    void onDefaultButtonClick(std::shared_ptr<MouseEvent> event);
    void onCancelButtonClick(std::shared_ptr<MouseEvent> event);
    void onSaveButtonClick(std::shared_ptr<MouseEvent> event);

};

}
#endif // FALLTERGEIST_SETTINGSMENUSTATE_H
