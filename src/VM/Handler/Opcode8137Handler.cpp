#include "../../VM/Handler/Opcode8137Handler.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Logger.h"
#include "../../State/State.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8137::Opcode8137(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8137::_run() {
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
