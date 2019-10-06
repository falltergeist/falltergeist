#include "Opcode80F0Handler.h"
#include "Game/Game.h"
#include "State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F0::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80F0] [=] void add_timer_event(void* obj, int time, int info)"
                                        << std::endl;
                int fixedParam = _script->dataStack()->popInteger();
                int delay = _script->dataStack()->popInteger();
                Game::Object *object = _script->dataStack()->popObject();
                auto state = Game::Game::getInstance()->locationState();
                if (state) {
                    state->addTimerEvent(object, delay, fixedParam);
                }
            }
        }
    }
}
