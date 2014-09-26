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

#ifndef FALLTERGEIST_PLAYERPANELSTATE_H
#define FALLTERGEIST_PLAYERPANELSTATE_H

// C++ standard inludes

// Falltergeist includes
#include "../Engine/State.h"

// Third party includes

namespace Falltergeist
{

class PlayerPanelState : public State
{
public:
    PlayerPanelState();
    virtual ~PlayerPanelState();

    virtual void init();
    virtual void render();
    virtual void think();
    virtual void handle(std::shared_ptr<Event> event);

    void onChangeHandButtonClick(std::shared_ptr<MouseEvent> event);
    void onPanelMouseDown(std::shared_ptr<MouseEvent> event);
    void onInventoryButtonClick(std::shared_ptr<MouseEvent> event);
    void onOptionsButtonClick(std::shared_ptr<MouseEvent> event);
    void onSkilldexButtonClick(std::shared_ptr<MouseEvent> event);
    void onPipBoyButtonClick(std::shared_ptr<MouseEvent> event);

};

}
#endif // FALLTERGEIST_PLAYERPANELSTATE_H
