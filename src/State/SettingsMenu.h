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

#ifndef FALLTERGEIST_SettingsMenu_H
#define FALLTERGEIST_SettingsMenu_H

// C++ standard includes
#include <map>

// Falltergeist includes
#include "State.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{
class TextArea;

namespace State
{

class SettingsMenu : public State
{
protected:
    std::map<std::string, TextArea*> _labels;
    TextArea* _addLabel(const std::string& name, TextArea* label);
    TextArea* _addTextArea(const std::string& message, unsigned int x, unsigned int y);
    TextArea* _addTextArea(TextArea* parent, unsigned int x, unsigned int y);
public:
    SettingsMenu();
    virtual ~SettingsMenu();
    virtual void init();
    virtual void think();

    void onDefaultButtonClick(MouseEvent* event);
    void doCancel();
    void doSave();

    virtual void onKeyDown(KeyboardEvent* event);

    virtual void onStateActivate(StateEvent* event);
    virtual void onStateDeactivate(StateEvent* event);
};

}
}

#endif // FALLTERGEIST_SettingsMenu_H
