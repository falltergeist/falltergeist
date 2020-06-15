#include "../../VM/Handler/Opcode8120Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8120::Opcode8120(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8120::_run()
            {
                logger->debug()
                    << "[8120] [=] void gSay_Message(int msg_list, int msg_num, int reaction)"
                    << std::endl
                ;
                _script->dataStack()->popInteger();
                _script->dataStack()->pop(); // string or integer
                _script->dataStack()->popInteger();
            }
        }
    }
}
