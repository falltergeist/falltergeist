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

#ifndef FALLTERGEIST_STATE_CRITTERINTERACT_H
#define FALLTERGEIST_STATE_CRITTERINTERACT_H

// C++ standard includes

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class State;
    }
    namespace Game
    {
        class CritterObject;
    }
    namespace VM
    {
        class Script;
    }
    namespace State
    {
        class CritterInteract : public State
        {
            public:
                CritterInteract();
                ~CritterInteract() override;

                void init() override;

                int backgroundID();
                void setBackgroundID(int backgroundID);

                int headID();
                void setHeadID(int headID);

                int mood();
                void setMood(int mood);

                Game::CritterObject* critter();
                void setCritter(Game::CritterObject* critter);

                int msgFileID();
                void setMsgFileID(int value);

                VM::Script* script();
                void setScript(VM::Script* script);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;

            protected:
                Point _oldCameraCenter;
                int _backgroundID = -1;
                int _headID = -1;
                int _mood = 0;
                int _msgFileID = -1;
                VM::Script* _script = nullptr;
                Game::CritterObject* _critter = nullptr;
        };
    }
}
#endif // FALLTERGEIST_STATE_CRITTERINTERACT_H
