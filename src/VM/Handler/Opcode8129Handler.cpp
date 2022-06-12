// Project includes
#include "../../VM/Handler/Opcode8129Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8129::Opcode8129(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8129::_run(VM::Script& script)
            {
                _logger->debug() << "[8129] [=] void gdialog_mod_barter(int modifier)" << std::endl;
                script.dataStack()->popInteger();
            }
        }
    }
}


