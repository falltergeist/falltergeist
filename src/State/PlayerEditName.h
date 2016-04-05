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

#ifndef FALLTERGEIST_STATE_PLAYEREDITNAME_H
#define FALLTERGEIST_STATE_PLAYEREDITNAME_H

// C++ standard includes
#include <map>

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace UI
    {
        class Rectangle;
        class TextArea;
    }
    namespace State
    {
        class PlayerEditName : public State
        {
            public:
                PlayerEditName();
                ~PlayerEditName() override;

                void init() override;
                void think() override;

                void onDoneButtonClick(Event::Mouse* event);
                void onTextAreaKeyDown(Event::Keyboard* event);

                void doDone();
                void doBack();

            protected:
                unsigned int _timer;
                UI::TextArea* _name = nullptr;
                UI::Rectangle* _cursor = nullptr;
                std::map<char,char> _keyCodes;
        };
    }
}
#endif // FALLTERGEIST_STATE_PLAYEREDITNAME_H
