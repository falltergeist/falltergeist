// Project includes
#include "../../VM/Handler/Opcode8032Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8032::Opcode8032(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8032::_run(VM::Script& script)
            {
                auto num = script.dataStack()->popInteger();
                auto value = script.dataStack()->values()->at(script.DVARbase() + num);
                script.dataStack()->push(value);
                _logger->debug()
                    << "[8032] [*] op_fetch " << "var" << std::hex << num << " type = "
                    << value.typeName() << std::endl
                ;
            }

        }
    }
}
