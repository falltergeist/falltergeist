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
            Opcode8152::Opcode8152(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8152::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8152] [=] void op_critter_set_flee_state(critter who, boolean flag)"
                    << std::endl
                ;
                // @TODO: add implementation
                script.dataStack()->popLogical();
                script.dataStack()->popObject();
            }
        }
    }
}
