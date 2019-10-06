#include "Opcode80C4.h"
#include "VM/Fallout/IStack.h"
#include "Game/Game.h"
#include "Game/Object.h"
#include "State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C4::applyTo(std::shared_ptr<IContext> context)
            {
                auto value = context->dataStack()->pop()->asInteger();
                auto num = context->dataStack()->pop()->asInteger();
                auto game = Game::getInstance();
                game->locationState()->setMVAR(num, value);
            }

            int Opcode80C4::number()
            {
                return 0x80C4;
            }

            std::string Opcode80C4::name()
            {
                return "MVAR[num] = value";
            }

            std::string Opcode80C4::notes()
            {
                return "";
            }
        }
    }
}


