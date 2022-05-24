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
            Opcode8105::Opcode8105(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8105::_run()
            {
                logger->debug() << "[8105] [+] string message_str(int msg_list, int msg_num);" << std::endl;
                auto msgNum = _script->dataStack()->popInteger();
                auto msgList = _script->dataStack()->popInteger();
                _script->dataStack()->push(_script->msgMessage(msgList, msgNum));
            }
        }
    }
}


