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

#ifndef FALLTERGEIST_GAMEDOORSCENERYOBJECT_H
#define FALLTERGEIST_GAMEDOORSCENERYOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/GameSceneryObject.h"

// Third party includes

namespace Falltergeist
{

class GameDoorSceneryObject : public GameSceneryObject
{
protected:
    bool _opened = false;
    bool _locked = false;
public:
    GameDoorSceneryObject();
    virtual ~GameDoorSceneryObject();

    bool opened();
    void setOpened(bool value);

    bool locked();
    void setLocked(bool value);

    virtual bool canWalkThru();

    virtual void use_p_proc();

    void onOpeningAnimationEnded(Event* event);
    void onClosingAnimationEnded(Event* event);
};

}
#endif // FALLTERGEIST_GAMEDOORSCENERYOBJECT_H
