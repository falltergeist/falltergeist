#include "Opcode8137Handler.h"
#include "Game/Game.h"
#include "Graphics/Renderer.h"
#include "State/State.h"
#include "VM/HaltException.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8137::applyTo(std::shared_ptr<IContext> context)
            {
                int time = _script->dataStack()->popInteger(); // original engine ignores time
                Logger::debug("SCRIPT") << "[8137] [=] void gfade_in(int time)" << std::endl
                                        << "    time = " << time << std::endl;

                auto state = Game::getInstance()->topState();
                state->scriptFade(_script, true);
                throw HaltException();
            }
        }
    }
}
