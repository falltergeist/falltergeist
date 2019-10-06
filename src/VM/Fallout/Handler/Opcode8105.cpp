#include "Opcode8105.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8105::applyTo(std::shared_ptr<IContext> context)
            {
                auto msgNum = context->dataStack()->pop()->asInteger();
                auto msgList = context->dataStack()->pop()->asInteger();
                context->dataStack()->push(context->msgMessage(msgList, msgNum));
            }

            int Opcode8105::number()
            {
                return 0x8105;
            }

            std::string Opcode8105::name()
            {
                return "string message_str(int msg_list, int msg_num)";
            }

            std::string Opcode8105::notes()
            {
                return "";
            }
        }
    }
}


