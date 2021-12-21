#include "../../VM/Handler/Opcode80DEHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
#include "../../UI/ResourceManager.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DE::Opcode80DE(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80DE::_run()
            {
                logger->debug()
                    << "[80DE] [*] void start_gdialog(int msgFileID, GameCritterObject* critter, int mood, int headID, int backgroundID)"
                    << std::endl
                ;
                int backgroundID = _script->dataStack()->popInteger();
                int headID = _script->dataStack()->popInteger();
                State::CritterInteract::Mood mood = static_cast<State::CritterInteract::Mood>(_script->dataStack()->popInteger());

                auto critter = dynamic_cast<Game::CritterObject *>(_script->dataStack()->popObject());
                if (!critter) {
                    _error("start_gdialog - wrong critter pointer");
                }

                int msgFileID = _script->dataStack()->popInteger();
                if (headID > -1) {
                    auto reaction = _script->LVARS()->at(0).integerValue();
                    logger->debug() << "Initial reaction: " << reaction << std::endl;
                    if (reaction <= -10) {
                        mood = State::CritterInteract::Mood::BAD;
                    } else if (reaction <= 10) {
                        mood = State::CritterInteract::Mood::NEUTRAL;
                    } else {
                        mood = State::CritterInteract::Mood::GOOD;
                    }
                }
                auto interact = new State::CritterInteract(std::make_shared<UI::ResourceManager>());
                interact->setBackgroundID(backgroundID);
                interact->setHeadID(headID);
                interact->setMood(mood);
                interact->setCritter(critter);
                interact->setMsgFileID(msgFileID);
                interact->setScript(_script);
                Game::Game::getInstance()->pushState(interact);
            }
        }
    }
}
