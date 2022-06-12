// Project includes
#include "../../VM/Handler/Opcode80AEHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AE::Opcode80AE(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80AE::_run(VM::Script& script)
            {
                _logger->debug() << "[80AE] [=] int do_check(ObjectPtr who, int check, int modifier)" << std::endl;
                auto dataStack = script.dataStack();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->push(2);
            }
        }
    }
}


