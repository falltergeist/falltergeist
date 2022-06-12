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
            OpcodeA001::OpcodeA001(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void OpcodeA001::_run()
            {
                union {
                    unsigned int iValue;
                    float fValue;
                } uValue;

                uValue.iValue = _script->intFile()->readValue();

                // Skip 4 bytes for read float value
                _script->setProgramCounter(_script->programCounter() + 4);
                _script->dataStack()->push(StackValue(uValue.fValue));

                logger->debug()
                    << "[A001] [*] push_d float" << std::endl
                    << "    value: " << std::to_string(uValue.fValue) << std::endl
                ;
            }
        }
    }
}
