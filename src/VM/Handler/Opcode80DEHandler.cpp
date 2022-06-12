// Project includes
#include "../../VM/Handler/Opcode80DEHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
#include "../../UI/ResourceManager.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DE::Opcode80DE(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80DE::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80DE] [*] void start_gdialog(int msgFileID, GameCritterObject* critter, int mood, int headID, int backgroundID)"
                    << std::endl
                ;
                int backgroundID = script.dataStack()->popInteger();
                int headID = script.dataStack()->popInteger();
                State::CritterInteract::Mood mood = static_cast<State::CritterInteract::Mood>(script.dataStack()->popInteger());

                auto critter = dynamic_cast<Game::CritterObject *>(script.dataStack()->popObject());
                if (!critter) {
                    _error("start_gdialog - wrong critter pointer");
                }

                int msgFileID = script.dataStack()->popInteger();
                if (headID > -1) {
                    auto reaction = script.LVARS()->at(0).integerValue();
                    _logger->debug() << "Initial reaction: " << reaction << std::endl;
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
                // TODO get rid of script dependency in state
                interact->setScript(&script);
                Game::Game::getInstance()->pushState(interact);
            }
        }
    }
}
