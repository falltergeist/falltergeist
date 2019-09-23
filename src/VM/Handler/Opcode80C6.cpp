#include "../../VM/Handler/Opcode80C6.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C6::applyTo(std::shared_ptr<IFalloutContext> context)
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


