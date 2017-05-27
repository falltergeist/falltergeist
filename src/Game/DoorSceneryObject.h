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

#ifndef FALLTERGEIST_GAME_DOORSCENERYOBJECT_H
#define FALLTERGEIST_GAME_DOORSCENERYOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/SceneryObject.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class Event;
    }

    namespace Game
    {
        /**
         * Doors. Can be opened, closed, locked and unlocked.
         */
        class DoorSceneryObject : public SceneryObject
        {
        public:
            DoorSceneryObject();
            ~DoorSceneryObject() override;

            bool opened() const;
            void setOpened(bool value);

            bool locked() const;
            void setLocked(bool value);

            bool canWalkThru() const override;

            void use_p_proc(CritterObject* usedBy) override;

            void onOpeningAnimationEnded(Event::Event* event);
            void onClosingAnimationEnded(Event::Event* event);

        protected:
            bool _opened = false;
            bool _locked = false;
        };
    }
}
#endif // FALLTERGEIST_GAME_DOORSCENERYOBJECT_H
