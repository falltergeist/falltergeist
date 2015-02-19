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

#ifndef FALLTERGEIST_CursorDropdown_H
#define FALLTERGEIST_CursorDropdown_H

// C++ standard includes
#include <vector>
#include <memory>

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class GameObject;
}
class Surface;
class HiddenMask;

namespace State
{

class CursorDropdown : public State
{
protected:
    Game::GameObject* _object;
    bool _onlyShowIcon;
    std::vector<int> _icons;
    int _initialX;
    int _initialY;
    int _currentSurface = 0;
    std::vector<UI*> _activeIcons;
    std::vector<UI*> _inactiveIcons;
    UI* _surface = 0;
    UI* _cursor = 0;
    bool _deactivated = false;
    unsigned int _initialMouseStack;
    
    void showMenu();
public:
    CursorDropdown(std::vector<int> icons, bool onlyIcon = false);
    virtual ~CursorDropdown();
    virtual void init();
    virtual void think();
    virtual void handle(Event* event);
    virtual void render();

    void onLeftButtonUp(MouseEvent* event);

    Game::GameObject* object();
    void setObject(Game::GameObject* object);

    virtual void onStateActivate(StateEvent* event);
    virtual void onStateDeactivate(StateEvent* event);

};

}
}

#endif // FALLTERGEIST_CursorDropdown_H
