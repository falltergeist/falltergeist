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
            Opcode80F4::Opcode80F4(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F4::_run()
            {
                logger->debug() << "[80F4] [=] int destroy_object(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                Game::Game::getInstance()->locationState()->destroyObject(object);
                _script->dataStack()->push(0);
            }
        }
    }
}
