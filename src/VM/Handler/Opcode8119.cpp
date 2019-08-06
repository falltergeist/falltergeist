#include "../../VM/Handler/Opcode8119.h"
#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8119::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                _script->dataStack()->push(Game::getInstance()->gameTime()->day());
            }

            int Opcode8119::number()
            {
                return 0x8119;
            }

            std::string Opcode8119::name()
            {
                return "int get_day()";
            }

            std::string Opcode8119::notes() {
                return "";
            }
        }
    }
}
