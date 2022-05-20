#include "../../VM/Handler/Opcode811DHandler.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode811D::Opcode811D(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode811D::_run()
            {
                logger->debug() << "[811D] [?] gsay_end" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog *>(Game::Game::getInstance()->topState());
                if (dialog->hasAnswers()) {
                    _script->dataStack()->push(0); // function return value
                    throw HaltException();
                }
                if (auto interact = dynamic_cast<Falltergeist::State::CritterInteract *>(Game::Game::getInstance()->topState(
                        1))) {
                    interact->switchSubState(State::CritterInteract::SubState::NONE);
                }
                //Game::getInstance()->popState(); // dialog state
            }
        }
    }
}


