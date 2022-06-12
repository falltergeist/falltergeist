// Project includes
#include "../../VM/Handler/OpcodeA001Handler.h"
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
            OpcodeA001::OpcodeA001(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void OpcodeA001::_run(VM::Script& script)
            {
                union {
                    unsigned int iValue;
                    float fValue;
                } uValue;

                uValue.iValue = script.intFile()->readValue();

                // Skip 4 bytes for read float value
                script.setProgramCounter(script.programCounter() + 4);
                script.dataStack()->push(StackValue(uValue.fValue));

                _logger->debug()
                    << "[A001] [*] push_d float" << std::endl
                    << "    value: " << std::to_string(uValue.fValue) << std::endl
                ;
            }
        }
    }
}
