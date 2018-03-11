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

#include "../Game/ContainerItemObject.h"

#include "../Game/Game.h"
#include "../State/Container.h"

namespace Falltergeist
{
    namespace Game
    {
        ContainerItemObject::ContainerItemObject() : ItemObject()
        {
            _subtype = Subtype::CONTAINER;
        }

        std::vector<ItemObject*>* ContainerItemObject::inventory()
        {
            return &_inventory;
        }

        void ContainerItemObject::use_p_proc(CritterObject* usedBy)
        {
            auto state = new State::Container();
            state->setObject(this);
            Game::getInstance()->pushState(state);
        }

        void ContainerItemObject::setLocked(bool locked)
        {
            this->_locked = locked;
        }

        bool ContainerItemObject::locked() const
        {
            return _locked;
        }

        void ContainerItemObject::setOpened(bool opened)
        {
            this->_opened = opened;
        }

        bool ContainerItemObject::opened() const
        {
            return _opened;
        }
    }
}
