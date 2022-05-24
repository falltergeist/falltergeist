// Project includes
#include "../../VM/Handler/Opcode8152Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8152::Opcode8152(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8152::_run()
            {
                logger->debug()
                    << "[8152] [=] void op_critter_set_flee_state(critter who, boolean flag)"
                    << std::endl
                ;
                // @TODO: add implementation
                _script->dataStack()->popLogical();
                _script->dataStack()->popObject();
            }
        }
    }
}
