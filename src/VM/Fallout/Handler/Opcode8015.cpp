#include "Game/Game.h"
#include "State/Location.h"
#include "Opcode8015.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8015::applyTo(std::shared_ptr<IContext> context)
            {
                std::string name = context->dataStack()->pop()->asString();
                auto value = context->dataStack()->pop();
                auto game = Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                (*EVARS)[name] = value;
            }

            int Opcode8015::number()
            {
                return 0x8015;
            }

            std::string Opcode8015::name()
            {
                return "void op_store_internal(string name, mixed value)";
            }

            std::string Opcode8015::notes()
            {
                return "";
            }
        }
    }
}
