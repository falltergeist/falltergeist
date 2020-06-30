#include "../../VM/Handler/Opcode80C1Handler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C1::Opcode80C1(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C1::_run()
            {
                logger->debug() << "[80C1] [*] LVAR[num]" << std::endl;
                unsigned int num = _script->dataStack()->popInteger();
                while (num >= _script->LVARS()->size()) {
                    _script->LVARS()->push_back(StackValue(0));
                }
                _script->dataStack()->push(_script->LVARS()->at(num));
            }
        }
    }
}
