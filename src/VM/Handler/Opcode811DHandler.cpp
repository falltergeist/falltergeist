#include "../../VM/Handler/Opcode811DHandler.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
#include "../../VM/HaltException.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode811D::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[811D] [?] gsay_end" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog *>(Game::getInstance()->topState());
                if (dialog->hasAnswers()) {
                    _script->dataStack()->push(0); // function return value
                    throw HaltException();
                }
                if (auto interact = dynamic_cast<Falltergeist::State::CritterInteract *>(Game::getInstance()->topState(
                        1))) {
                    interact->switchSubState(State::CritterInteract::SubState::NONE);
                }
                //Game::getInstance()->popState(); // dialog state
            }
        }
    }
}


