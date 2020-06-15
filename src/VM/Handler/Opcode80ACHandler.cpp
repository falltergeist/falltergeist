#include "../../VM/Handler/Opcode80ACHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AC::Opcode80AC(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80AC::_run()
            {
                logger->debug() << "[80AC] [=] int roll_vs_skill(ObjectPtr who, int skill, int modifier)"
                                        << std::endl;
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->push(2);
            }
        }
    }
}
