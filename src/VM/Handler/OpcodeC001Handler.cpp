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
            OpcodeC001::OpcodeC001(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void OpcodeC001::_run(VM::Script& script)
            {
                int value = script.intFile()->readValue();

                // Skip 4 bytes for readed integer value
                script.setProgramCounter(script.programCounter() + 4);
                script.dataStack()->push(StackValue(value));

                _logger->debug()
                    << "[C001] [*] push_d integer" << std::endl
                    << "    value: " << std::to_string(value) << std::endl
                ;
            }
        }
    }
}
