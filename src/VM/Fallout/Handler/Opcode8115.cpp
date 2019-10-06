#include "Game/Game.h"
#include "State/Movie.h"
#include "Opcode8115.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8115::applyTo(std::shared_ptr<IContext> context)
            {
                int movie =  context->dataStack()->pop()->asInteger();
                auto state = new State::Movie(movie);
                Game::Game::getInstance()->pushState(state);
            }

            int Opcode8115::number()
            {
                return 0x8115;
            }

            std::string Opcode8115::name()
            {
                return "void playMovie(int movie)";
            }

            std::string Opcode8115::notes()
            {
                return "";
            }
        }
    }
}
