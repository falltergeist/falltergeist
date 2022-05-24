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
            Opcode80E3::Opcode80E3(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E3::_run()
            {
                logger->debug() << "[80E3] [=] void set_obj_visibility(void* obj, int visibility)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}
