// Project includes
#include "../../VM/Handler/Opcode80CDHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80CD::Opcode80CD(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80CD::_run(VM::Script& script)
            {
                _logger->debug() << "[80CD] [=] void animate_stand_reverse_obj(void* obj)" << std::endl;
                script.dataStack()->popObject();
            }
        }
    }
}
