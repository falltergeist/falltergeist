// Project includes
#include "../../VM/Handler/Opcode8012Handler.h"
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
            Opcode8012::Opcode8012(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8012::_run(VM::Script& script)
            {
                auto number = script.dataStack()->popInteger();
                auto value = script.dataStack()->values()->at(script.SVARbase() + number);
                script.dataStack()->push(value);

                _logger->debug()
                    << "[8012] [*] value = op_fetch_global[num]" << std::endl
                    << "      num: " << number << std::endl
                    << "     type: " << value.typeName() << std::endl
                    << "    value: " << value.toString()
                    << std::endl
                ;
            }
        }
    }
}
