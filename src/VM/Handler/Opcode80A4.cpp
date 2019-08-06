#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../VM/Handler/Opcode80A4.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"
#include "../../VM/FalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A4::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto object = context->dataStack()->pop()->asObject();
                context->dataStack()->push(std::make_shared<FalloutValue>(object->name()));
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


