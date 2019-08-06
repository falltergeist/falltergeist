#include "../../VM/Handler/Opcode8136Handler.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Logger.h"
#include "../../State/State.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8136::Opcode8136(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8136::_run() {
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
