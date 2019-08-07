#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../VM/Handler/Opcode80BF.h"
#include "../../VM/FalloutValue.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BF::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto game = Game::getInstance();
                context->dataStack()->push(std::make_shared<FalloutValue>(game->player()));
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


