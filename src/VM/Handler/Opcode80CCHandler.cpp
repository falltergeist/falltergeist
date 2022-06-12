// Project includes
#include "../../VM/Handler/Opcode80CCHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CC::Opcode80CC(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80CC::_run(VM::Script& script)
            {
                _logger->debug() << "[80CC] [=] void animate_stand_obj(void* obj)" << std::endl;
                script.dataStack()->popObject();
            }
        }
    }
}
