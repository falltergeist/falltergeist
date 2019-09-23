#include "../../VM/Handler/Opcode8123.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"
#include "../../Game/CritterObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8123::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto critter = std::dynamic_pointer_cast<Game::CritterObject>(context->dataStack()->pop()->asObject());
                auto value = critter->poisonLevel();
                context->dataStack()->push(value);
            }

            int Opcode8123::number()
            {
                return 0x8123;
            }

            std::string Opcode8123::name()
            {
                return "int value = GetPoison(GameCritterObject* critter)";
            }

            std::string Opcode8123::notes()
            {
                return "";
            }
        }
    }
}
