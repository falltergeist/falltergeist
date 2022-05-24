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
            Opcode80E4::Opcode80E4(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E4::_run()
            {
                logger->debug() << "[80E4] [=] void load_map(string* map, int param)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}
