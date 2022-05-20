#include "../../VM/Handler/Opcode8013Handler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8013::Opcode8013(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8013::_run()
            {
                auto number = _script->dataStack()->popInteger();
                auto value = _script->dataStack()->pop();
                _script->dataStack()->values()->at(_script->SVARbase() + number) = value;

                auto &debug = logger->debug();

                debug << "[8013] [*] op_store_global" << std::endl
                      << "      num: " << number << std::endl
                      << "     type: " << value.typeName() << std::endl
                      << "    value: " << value.toString();

                debug << std::endl;
            }
        }
    }
}
