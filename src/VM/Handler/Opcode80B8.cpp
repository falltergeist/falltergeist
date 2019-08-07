#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Handler/Opcode80B8.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B8::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto value = context->dataStack()->pop()->asString();
                auto game = Game::getInstance();
                game->locationState()->displayMessage(value);
            }

            int Opcode80B8::number()
            {
                return 0x80B8;
            }

            std::string Opcode80B8::name()
            {
                return "void display_msg(string)";
            }

            std::string Opcode80B8::notes()
            {
                return "";
            }
        }
    }
}
