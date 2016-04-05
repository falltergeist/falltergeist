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

#ifndef FALLTERGEIST_STATE_SETTINGSMENU_H
#define FALLTERGEIST_STATE_SETTINGSMENU_H

// C++ standard includes
#include <map>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class Mouse;
        class State;
    }
    namespace UI
    {
        class TextArea;
    }
    namespace State
    {
        class SettingsMenu : public State
        {
            public:
                SettingsMenu();
                ~SettingsMenu() override;

                void init() override;
                void think() override;

                void onDefaultButtonClick(Event::Mouse* event);
                void doCancel();
                void doSave();

                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
            protected:
                std::map<std::string, UI::TextArea*> _labels;
                UI::TextArea* _addLabel(const std::string& name, UI::TextArea* label);
                UI::TextArea* _addTextArea(const std::string& message, unsigned int x, unsigned int y);
                UI::TextArea* _addTextArea(UI::TextArea* parent, unsigned int x, unsigned int y);
        };
    }
}
#endif // FALLTERGEIST_STATE_SETTINGSMENU_H
