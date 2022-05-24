// Project includes
#include "../../VM/Handler/Opcode8143Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8143::Opcode8143(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8143::_run()
            {
                logger->debug() << "[8143] [=] void attack_setup(ObjectPtr who, ObjectPtr victim)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}
