#include "../../VM/Handler/Opcode811CHandler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterDialogReview.h"
#include "../../State/CritterInteract.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode811C::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[811C] [?] gsay_start" << std::endl;

                if (auto interact = dynamic_cast<Falltergeist::State::CritterInteract *>(Game::getInstance()->topState())) {
                    interact->dialogReview()->setCritterName(_script->owner()->scrName());
                    interact->switchSubState(State::CritterInteract::SubState::DIALOG);
                }
            }
        }
    }
}
