// Project includes
#include "../../VM/Handler/Opcode8143Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8143::Opcode8143(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8143::_run(VM::Script& script)
            {
                _logger->debug() << "[8143] [=] void attack_setup(ObjectPtr who, ObjectPtr victim)" << std::endl;
                script.dataStack()->popObject();
                script.dataStack()->popObject();
            }
        }
    }
}
