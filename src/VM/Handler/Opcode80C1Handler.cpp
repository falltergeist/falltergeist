// Project includes
#include "../../VM/Handler/Opcode80C1Handler.h"
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
            Opcode80C1::Opcode80C1(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80C1::_run(VM::Script& script)
            {
                _logger->debug() << "[80C1] [*] LVAR[num]" << std::endl;
                unsigned int num = script.dataStack()->popInteger();
                while (num >= script.LVARS()->size()) {
                    script.LVARS()->push_back(StackValue(0));
                }
                script.dataStack()->push(script.LVARS()->at(num));
            }
        }
    }
}
