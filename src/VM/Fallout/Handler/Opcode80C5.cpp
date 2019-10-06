#include "Opcode80C5.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStackValue.h"
#include "Game/Game.h"
#include "Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C5::applyTo(std::shared_ptr<IContext> context)
            {
                int num = context->dataStack()->pop()->asInteger();
                int value;
                if (num < 0) {
                    value = 0;
                } else {
                    auto game = Game::getInstance();
                    value = game->GVAR(num);
                }
                context->dataStack()->push(value);
            }

            int Opcode80C5::number()
            {
                return 0x80C5;
            }

            std::string Opcode80C5::name()
            {
                return "GVAR[num]";
            }

            std::string Opcode80C5::notes()
            {
                return "";
            }
        }
    }
}
