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
#include "../Game/Timer.h"

// Third party includes

namespace Falltergeist
{
    namespace Format
    {
        namespace Lip
        {
            class File;
        }
    }
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
        class CritterDialog;
        class CritterBarter;
        class CritterDialogReview;

        class CritterInteract : public State
        {
            public:
                enum class Phase {
                    FIDGET = 0,
                    TRANSITION,
                    TALK
                };

                enum class Mood {
                    GOOD = 1,
                    NEUTRAL = 4,
                    BAD = 7
                };

                enum class Reaction {
                    GOOD = 49,
                    NEUTRAL = 50,
                    BAD = 51
                };

                enum class SubState {
                    NONE= 0,
                    DIALOG,
                    BARTER,
                    REVIEW,
                    CONTROL
                };
                virtual void think() override;

                CritterInteract();
                ~CritterInteract() override;

                void init() override;

                int backgroundID();
                void setBackgroundID(int backgroundID);

                int headID();
                void setHeadID(int headID);

                Mood mood();
                void setMood(Mood mood);

                Game::CritterObject* critter();
                void setCritter(Game::CritterObject* critter);

                int msgFileID();
                void setMsgFileID(int value);

                VM::Script* script();
                void setScript(VM::Script* script);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;

                void playSpeech(const std::string& speech);

                CritterDialog* dialog();
                CritterDialogReview* dialogReview();
                CritterBarter* barter();
                void switchSubState(SubState state);
                void transition(Reaction reaction);
                void onMoodTransitionEnded(Event::Event* event);


        protected:
                Point _oldCameraCenter;
                int _backgroundID = -1;
                int _headID = -1;
                Mood _mood = Mood::NEUTRAL;
                int _msgFileID = -1;
                VM::Script* _script = nullptr;
                Game::CritterObject* _critter = nullptr;
                std::string _headName;
                uint32_t _startTime;
                uint32_t _nextIndex;
                Phase _phase = Phase::FIDGET;
                Format::Lip::File* _lips = nullptr;
                int32_t _goodFidgets;
                int32_t _neutralFidgets;
                int32_t _badFidgets;
                Game::Timer _fidgetTimer;

                CritterDialog* _dialog;
                CritterBarter* _barter;
                CritterDialogReview* _review;

                SubState _state = SubState::NONE;

        };
    }
}
#endif // FALLTERGEIST_STATE_CRITTERINTERACT_H
