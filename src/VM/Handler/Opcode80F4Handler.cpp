// Project includes
#include "../../VM/Handler/Opcode80F4Handler.h"
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
            Opcode80F4::Opcode80F4(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80F4::_run(VM::Script& script)
            {
                _logger->debug() << "[80F4] [=] int destroy_object(void* obj)" << std::endl;
                auto object = script.dataStack()->popObject();
                Game::Game::getInstance()->locationState()->destroyObject(object);
                script.dataStack()->push(0);
            }
        }
    }
}
