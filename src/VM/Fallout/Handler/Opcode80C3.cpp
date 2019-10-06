#include "Opcode80C3.h"
#include "Game/Game.h"
#include "State/Location.h"
#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C3::applyTo(std::shared_ptr<IContext> context)
            {
                auto num = context->dataStack()->pop()->asInteger();
                if (num < 0) {
                    context->dataStack()->push(0);
                }
                auto game = Game::getInstance();
                context->dataStack()->push(game->locationState()->MVAR(num));
            }

            int Opcode80C3::number()
            {
                return 0x80C3;
            }

            std::string Opcode80C3::name()
            {
                return "MVAR[num]";
            }

            std::string Opcode80C3::notes()
            {
                return "";
            }
        }
    }
}
