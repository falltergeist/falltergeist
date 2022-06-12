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
            Opcode80A6::Opcode80A6(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80A6::_run(VM::Script& script)
            {
                _logger->debug() << "[80A6] [=] int SkillPoints(int PCStatNum)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->push(0);
            }
        }
    }
}
