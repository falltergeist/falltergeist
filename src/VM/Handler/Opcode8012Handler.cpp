#include "../../VM/Handler/Opcode8012Handler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8012::Opcode8012(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8012::_run()
            {
                auto number = _script->dataStack()->popInteger();
                auto value = _script->dataStack()->values()->at(_script->SVARbase() + number);
                _script->dataStack()->push(value);

                logger->debug()
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
