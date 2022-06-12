// Project includes
#include "../../VM/Handler/Opcode8139Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8139::Opcode8139(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8139::_run(VM::Script& script)
            {
                _logger->debug() << "[8139] [=] int item_caps_adjust(void* obj, int amount)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
                script.dataStack()->push(0);
            }
        }
    }
}


