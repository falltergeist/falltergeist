#include "../../VM/Handler/Opcode80F1Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F1::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80F1] [=] void rm_timer_event (void* obj)" << std::endl;
                Game::Object *object = _script->dataStack()->popObject();
                auto state = Game::Game::getInstance()->locationState();
                if (state) {
                    state->removeTimerEvent(object);
                }
            }
        }
    }
}


