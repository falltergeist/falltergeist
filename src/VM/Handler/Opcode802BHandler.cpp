// Project includes
#include "../../VM/Handler/Opcode802BHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode802B::Opcode802B(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode802B::_run(VM::Script& script)
            {
                auto argumentsCounter = script.dataStack()->popInteger();
                script.returnStack()->push(static_cast<unsigned>(script.DVARbase()));
                script.setDVARBase(script.dataStack()->size() - argumentsCounter);
                _logger->debug() << "[802B] [*] op_push_base = " << script.DVARbase() << std::endl;
            }

        }
    }
}
