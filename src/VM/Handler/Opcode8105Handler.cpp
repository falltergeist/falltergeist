// Project includes
#include "../../VM/Handler/Opcode8105Handler.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8105::Opcode8105(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8105::_run(VM::Script& script)
            {
                _logger->debug() << "[8105] [+] string message_str(int msg_list, int msg_num);" << std::endl;
                auto msgNum = script.dataStack()->popInteger();
                auto msgList = script.dataStack()->popInteger();
                script.dataStack()->push(script.msgMessage(msgList, msgNum));
            }
        }
    }
}


