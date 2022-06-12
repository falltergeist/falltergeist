// Project includes
#include "../../VM/Handler/Opcode811CHandler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterDialogReview.h"
#include "../../State/CritterInteract.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode811C::Opcode811C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode811C::_run(VM::Script& script)
            {
                _logger->debug() << "[811C] [?] gsay_start" << std::endl;

                if (auto interact = dynamic_cast<Falltergeist::State::CritterInteract *>(Game::Game::getInstance()->topState())) {
                    interact->dialogReview()->setCritterName(script.owner()->scrName());
                    interact->switchSubState(State::CritterInteract::SubState::DIALOG);
                }
            }
        }
    }
}
