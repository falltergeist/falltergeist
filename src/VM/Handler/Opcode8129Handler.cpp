#include "../../VM/Handler/Opcode8129Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8129::Opcode8129(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8129::_run()
            {
                logger->debug() << "[8129] [=] void gdialog_mod_barter(int modifier)" << std::endl;
                _script->dataStack()->popInteger();
            }
        }
    }
}


