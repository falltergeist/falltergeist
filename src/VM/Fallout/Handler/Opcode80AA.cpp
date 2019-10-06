#include "Exception.h"
#include "Game/CritterObject.h"
#include "Opcode80AA.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AA::applyTo(std::shared_ptr<IContext> context)
            {
                int skill = context->dataStack()->pop()->asInteger();
                if (skill > 17 || skill < 0) {
                    throw Exception("get_skill_value - skill out of range: " + std::to_string(skill));
                }
                auto object = context->dataStack()->pop()->asObject();
                int value = 0;
                if (auto critter = std::dynamic_pointer_cast<Game::CritterObject>(object)) {
                    value = critter->skillValue((SKILL) skill);
                    context->dataStack()->push(value);
                } else {
                    throw Exception("get_skill_value(who, skill): who is not critter");
                }
            }

            int Opcode80AA::number()
            {
                return 0x80AA;
            }

            std::string Opcode80AA::name()
            {
                return "int get_skill_value(GameCritterObject* who, int skill)";
            }

            std::string Opcode80AA::notes()
            {
                return "";
            }
        }
    }
}


