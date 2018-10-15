/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GAME_CONTAINERITEMOBJECT_H
#define FALLTERGEIST_GAME_CONTAINERITEMOBJECT_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Game/ItemObject.h"

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Items able to hold other items in their inventory.
         */
        class ContainerItemObject : public ItemObject
        {
            public:
                ContainerItemObject();
                ~ContainerItemObject() override = default;

                std::vector<ItemObject*>* inventory();

                void use_p_proc(CritterObject* usedBy) override;

                bool locked() const;
                void setLocked(bool locked);

                bool opened() const;
                void setOpened(bool opened);

            protected:
                std::vector<ItemObject*> _inventory;
                bool _opened = false;
                bool _locked = false;
        };
    }
}

#endif // FALLTERGEIST_GAME_CONTAINERITEMOBJECT_H
