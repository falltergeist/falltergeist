// Project includes
#include "../../VM/Handler/Opcode8031Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8031::Opcode8031(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8031::_run(VM::Script& script)
            {
                auto num = script.dataStack()->popInteger();
                auto value = script.dataStack()->pop();
                _logger->debug()
                    << "[8031] [*] op_store " << "var" << std::hex << num << " type = "
                    << value.typeName() << std::endl
                ;
                script.dataStack()->values()->at(script.DVARbase() + num) = value;
            }
        }
    }
}
