// Project includes
#include "../../VM/Handler/Opcode80E4Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E4::Opcode80E4(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80E4::_run(VM::Script& script)
            {
                _logger->debug() << "[80E4] [=] void load_map(string* map, int param)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
            }
        }
    }
}
