#include "../../VM/Handler/Opcode80AEHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AE::Opcode80AE(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80AE::_run()
            {
                logger->debug() << "[80AE] [=] int do_check(ObjectPtr who, int check, int modifier)" << std::endl;
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->push(2);
            }
        }
    }
}


