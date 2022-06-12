// Project includes
#include "../../VM/Handler/Opcode8120Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8120::Opcode8120(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8120::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8120] [=] void gSay_Message(int msg_list, int msg_num, int reaction)"
                    << std::endl
                ;
                script.dataStack()->popInteger();
                script.dataStack()->pop(); // string or integer
                script.dataStack()->popInteger();
            }
        }
    }
}
