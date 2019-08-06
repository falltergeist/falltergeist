#include "../../Logger.h"
#include "../../VM/Handler/Opcode8120.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8120::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                _script->dataStack()->popInteger();
                _script->dataStack()->pop(); // string or integer
                _script->dataStack()->popInteger();
            }

            int Opcode8120::number()
            {
                return 0x8120;
            }

            std::string Opcode8120::name()
            {
                return "void gSay_Message(int msg_list, int msg_num, int reaction)";
            }

            std::string Opcode8120::notes()
            {
                return "";
            }
        }
    }
}
