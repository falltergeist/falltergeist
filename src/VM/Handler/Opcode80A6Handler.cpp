// Project includes
#include "../../VM/Handler/Opcode80A6Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A6::Opcode80A6(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80A6::_run()
            {
                logger->debug() << "[80A6] [=] int SkillPoints(int PCStatNum)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->push(0);
            }
        }
    }
}
