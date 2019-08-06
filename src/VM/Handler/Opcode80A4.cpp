#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Logger.h"
#include "../../VM/Handler/Opcode80A4.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A4::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto object = _script->dataStack()->popObject();
                _script->dataStack()->push(object->name());
            }

            int Opcode80A4::number()
            {
                return 0x80A4;
            }

            std::string Opcode80A4::name()
            {
                return "std::string* obj_name(GameCritterObject* who)";
            }

            std::string Opcode80A4::notes() {
                return "";
            }
        }
    }
}


