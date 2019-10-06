#include "Game/DudeObject.h"
#include "Game/Game.h"
#include "Opcode80BF.h"
#include "VM/Fallout/StackValue.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BF::applyTo(std::shared_ptr<IContext> context)
            {
                auto game = Game::getInstance();
                context->dataStack()->push(std::make_shared<StackValue>(game->player()));
            }

            int Opcode80BF::number()
            {
                return 0x80BF;
            }

            std::string Opcode80BF::name()
            {
                return "GameDudeObject* dude_obj()";
            }

            std::string Opcode80BF::notes()
            {
                return "";
            }
        }
    }
}


