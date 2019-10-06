#pragma once

#include "../State/State.h"
#include "../Game/Timer.h"

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
