#include "Game/CritterObject.h"
#include "Game/Game.h"
#include "Opcode80A4.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A4::applyTo(std::shared_ptr<IContext> context)
            {
                auto object = context->dataStack()->pop()->asObject();
                context->dataStack()->push(std::make_shared<StackValue>(object->name()));
            }

            int Opcode80A4::number()
            {
                return 0x80A4;
            }

            std::string Opcode80A4::name()
            {
                return "std::string* obj_name(GameCritterObject* who)";
            }

            std::string Opcode80A4::notes()
            {
                return "";
            }
        }
    }
}


