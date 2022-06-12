// Project includes
#include "../../VM/Handler/Opcode80F1Handler.h"
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
            Opcode80F1::Opcode80F1(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F1::_run(VM::Script& script)
            {
                _logger->debug() << "[80F1] [=] void rm_timer_event (void* obj)" << std::endl;
                Game::Object *object = script.dataStack()->popObject();
                auto state = Game::Game::getInstance()->locationState();
                if (state) {
                    state->removeTimerEvent(object);
                }
            }
        }
    }
}


