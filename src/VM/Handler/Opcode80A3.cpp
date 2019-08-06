#include "../../VM/Handler/Opcode80A3.h"
#include "../../Audio/Mixer.h"
#include "../../Game/Game.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A3::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto name = context->dataStack()->pop()->asString();
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/" + name + ".acm");
            }

            int Opcode80A3::number()
            {
                return 0x80A3;
            }

            std::string Opcode80A3::name()
            {
                return "void play_sfx(string* p1)";
            }

            std::string Opcode80A3::notes()
            {
                return "";
            }
        }
    }
}


