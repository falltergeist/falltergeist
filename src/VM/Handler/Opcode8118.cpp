#include "../../Game/Game.h"
#include "../../Game/Time.h"
#include "../../Logger.h"
#include "../../VM/Handler/Opcode8118.h"
#include "../../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8118::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                _script->dataStack()->push(Game::getInstance()->gameTime()->month());
            }

            int Opcode8118::number()
            {
                return 0x8118;
            }

            std::string Opcode8118::name()
            {
                return "int get_month";
            }

            std::string Opcode8118::notes()
            {
                return "";
            }
        }
    }
}
