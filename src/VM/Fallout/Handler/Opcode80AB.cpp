#include "Opcode80AB.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AB::applyTo(std::shared_ptr<IContext> context)
            {
                // @TODO: implement
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asObject();
                context->dataStack()->push((int)0);
            }

            int Opcode80AB::number()
            {
                return 0x80AB;
            }

            std::string Opcode80AB::name()
            {
                return "int using_skill(GameCritterObject* who, int skill)";
            }

            std::string Opcode80AB::notes()
            {
                return "";
            }
        }
    }
}
