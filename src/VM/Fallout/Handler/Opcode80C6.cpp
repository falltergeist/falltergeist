#include "Opcode80C6.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "Game/Game.h"
#include "Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C6::applyTo(std::shared_ptr<IContext> context)
            {
                auto value = context->dataStack()->pop()->asInteger();
                auto num = context->dataStack()->pop()->asInteger();
                auto game = Game::getInstance();
                game->setGVAR(num, value);
            }

            int Opcode80C6::number()
            {
                return 0x80C6;
            }

            std::string Opcode80C6::name()
            {
                return "GVAR[num] = value";
            }

            std::string Opcode80C6::notes()
            {
                return "";
            }
        }
    }
}


