// Project includes
#include "../../VM/Handler/Opcode80E3Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E3::Opcode80E3(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80E3::_run(VM::Script& script)
            {
                _logger->debug() << "[80E3] [=] void set_obj_visibility(void* obj, int visibility)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
            }
        }
    }
}
