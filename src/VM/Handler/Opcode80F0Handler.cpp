// Project includes
#include "../../VM/Handler/Opcode80F0Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80F0::Opcode80F0(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F0::_run()
            {
                logger->debug()
                    << "[80F0] [=] void add_timer_event(void* obj, int time, int info)"
                    << std::endl
                ;
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
