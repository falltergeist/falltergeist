// Project includes
#include "../../VM/Handler/Opcode8013Handler.h"
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
            Opcode8013::Opcode8013(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode8013::_run(VM::Script& script)
            {
                auto number = script.dataStack()->popInteger();
                auto value = script.dataStack()->pop();
                script.dataStack()->values()->at(script.SVARbase() + number) = value;

                auto &debug = _logger->debug();

                debug << "[8013] [*] op_store_global" << std::endl
                      << "      num: " << number << std::endl
                      << "     type: " << value.typeName() << std::endl
                      << "    value: " << value.toString();

                debug << std::endl;
            }
        }
    }
}
