// Project includes
#include "../../VM/Handler/OpcodeC001Handler.h"
#include "../../Format/Int/File.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            OpcodeC001::OpcodeC001(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void OpcodeC001::_run()
            {
                int value = _script->script()->readValue();

                // Skip 4 bytes for readed integer value
                _script->setProgramCounter(_script->programCounter() + 4);
                _script->dataStack()->push(StackValue(value));

                logger->debug()
                    << "[C001] [*] push_d integer" << std::endl
                    << "    value: " << std::to_string(value) << std::endl
                ;
            }
        }
    }
}
