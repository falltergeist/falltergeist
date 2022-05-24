// Project includes
#include "../../VM/Handler/Opcode80C2Handler.h"
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
            Opcode80C2::Opcode80C2(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C2::_run()
            {
                logger->debug() << "[80C2] [*] LVAR[num] = value" << std::endl;
                auto value = _script->dataStack()->pop();
                unsigned int num = _script->dataStack()->popInteger();
                while (num >= _script->LVARS()->size()) {
                    _script->LVARS()->push_back(StackValue(0));
                }
                _script->LVARS()->at(num) = value;
            }
        }
    }
}


