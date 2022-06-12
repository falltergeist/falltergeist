// Project includes
#include "../../VM/Handler/Opcode8138Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8138::Opcode8138(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8138::_run(VM::Script& script)
            {
                _logger->debug() << "[8138] [=] int item_caps_total(void* obj)" << std::endl;
                script.dataStack()->popObject();
                script.dataStack()->push(0);
            }
        }
    }
}
