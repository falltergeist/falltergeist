// Project includes
#include "../../VM/Handler/Opcode8150Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8150::Opcode8150(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8150::_run(VM::Script& script)
            {
                _logger->debug() << "[8150] [=] int obj_on_screen(void* obj)" << std::endl;
                script.dataStack()->popObject();
                script.dataStack()->push(1);
            }
        }
    }
}
