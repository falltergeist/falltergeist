#include "../../VM/Handler/Opcode8105.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8105::applyTo(std::shared_ptr<IFalloutContext> context)
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


