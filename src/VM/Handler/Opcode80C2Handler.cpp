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
            Opcode80C2::Opcode80C2(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80C2::_run(VM::Script& script)
            {
                _logger->debug() << "[80C2] [*] LVAR[num] = value" << std::endl;
                auto value = script.dataStack()->pop();
                unsigned int num = script.dataStack()->popInteger();
                while (num >= script.LVARS()->size()) {
                    script.LVARS()->push_back(StackValue(0));
                }
                script.LVARS()->at(num) = value;
            }
        }
    }
}


