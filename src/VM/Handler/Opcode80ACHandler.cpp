// Project includes
#include "../../VM/Handler/Opcode80ACHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AC::Opcode80AC(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80AC::_run(VM::Script& script)
            {
                _logger->debug() << "[80AC] [=] int roll_vs_skill(ObjectPtr who, int skill, int modifier)"
                                        << std::endl;
                auto dataStack = script.dataStack();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->push(2);
            }
        }
    }
}
