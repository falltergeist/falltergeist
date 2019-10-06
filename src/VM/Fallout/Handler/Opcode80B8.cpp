#include "Game/Game.h"
#include "State/Location.h"
#include "Opcode80B8.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B8::applyTo(std::shared_ptr<IContext> context)
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
