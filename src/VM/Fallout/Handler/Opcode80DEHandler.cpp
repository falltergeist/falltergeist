#include "Opcode80DEHandler.h"
#include "Game/CritterObject.h"
#include "Game/Game.h"
#include "State/CritterDialog.h"
#include "State/CritterInteract.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80DE::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT")
                        << "[80DE] [*] void start_gdialog(int msgFileID, GameCritterObject* critter, int mood, int headID, int backgroundID)"
                        << std::endl;
                int backgroundID = _script->dataStack()->popInteger();
                int headID = _script->dataStack()->popInteger();
                State::CritterInteract::Mood mood = static_cast<State::CritterInteract::Mood>(_script->dataStack()->popInteger());

                auto critter = dynamic_cast<Game::CritterObject *>(_script->dataStack()->popObject());
                if (!critter) _error("start_gdialog - wrong critter pointer");

                int msgFileID = _script->dataStack()->popInteger();
                if (headID > -1) {
                    auto reaction = _script->LVARS()->at(0).integerValue();
                    Logger::debug("SCRIPT") << "Initial reaction: " << reaction << std::endl;
                    if (reaction <= -10) {
                        mood = State::CritterInteract::Mood::BAD;
                    } else if (reaction <= 10) {
                        mood = State::CritterInteract::Mood::NEUTRAL;
                    } else {
                        mood = State::CritterInteract::Mood::GOOD;
                    }
                }
                auto interact = new State::CritterInteract();
                interact->setBackgroundID(backgroundID);
                interact->setHeadID(headID);
                interact->setMood(mood);
                interact->setCritter(critter);
                interact->setMsgFileID(msgFileID);
                interact->setScript(_script);
                Game::getInstance()->pushState(interact);
            }
        }
    }
}
