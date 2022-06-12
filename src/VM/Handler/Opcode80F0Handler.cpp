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
            Opcode80F0::Opcode80F0(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F0::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80F0] [=] void add_timer_event(void* obj, int time, int info)"
                    << std::endl
                ;
                int fixedParam = script.dataStack()->popInteger();
                int delay = script.dataStack()->popInteger();
                Game::Object *object = script.dataStack()->popObject();
                auto state = Game::Game::getInstance()->locationState();
                if (state) {
                    state->addTimerEvent(object, delay, fixedParam);
                }
            }
        }
    }
}
