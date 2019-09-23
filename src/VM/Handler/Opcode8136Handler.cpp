#include "../../VM/Handler/Opcode8136Handler.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../State/State.h"
#include "../../VM/HaltException.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8136::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                int time = _script->dataStack()->popInteger(); // original engine ignores time
                Logger::debug("SCRIPT") << "[8136] [=] void gfade_out(int time)" << std::endl
                                        << "    time = " << time << std::endl;

                auto state = Game::getInstance()->topState();
                state->scriptFade(_script, false);
                throw HaltException();
            }
        }
    }
}
