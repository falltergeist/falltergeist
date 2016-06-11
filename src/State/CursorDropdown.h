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

#ifndef FALLTERGEIST_STATE_CURSORDROPDOWN_H
#define FALLTERGEIST_STATE_CURSORDROPDOWN_H

// C++ standard includes
#include <memory>
#include <vector>

// Falltergeist includes
#include "../Input/Mouse.h"
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class Event;
        class Mouse;
    }
    namespace Game
    {
        class Object;
    }
    namespace State
    {
        class CursorDropdown : public State
        {
            public:
                CursorDropdown(std::vector<Input::Mouse::Icon>&& icons, bool onlyIcon = false);
                ~CursorDropdown() override;

                void init() override;
                void think() override;
                void handle(Event::Event* event) override;
                void render() override;

                void onLeftButtonUp(Event::Mouse* event);

                Game::Object* object();
                void setObject(Game::Object* object);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;

            protected:
                Game::Object* _object = nullptr;
                bool _onlyShowIcon;
                std::vector<Input::Mouse::Icon> _icons;
                int _initialX;
                int _initialY;
                int _currentIcon = 0;
                std::vector<std::unique_ptr<UI::Base>> _activeIcons;
                std::vector<std::unique_ptr<UI::Base>> _inactiveIcons;
                UI::Base* _cursor = nullptr;
                Point _iconsPos;
                bool _deactivated = false;
                unsigned int _initialMouseStack;

                Event::MouseHandler _mouseDownHandler, _mouseUpHandler, _mouseMoveHandler;

                void showMenu();
        };
    }
}
#endif // FALLTERGEIST_STATE_CURSORDROPDOWN_H
