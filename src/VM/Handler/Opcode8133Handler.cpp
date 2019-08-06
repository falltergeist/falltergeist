#include "../../VM/Handler/Opcode8133Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8133::Opcode8133(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8133::_run() {
                Logger::debug("SCRIPT") << "[8134] [=] void game_ui_disable()" << std::endl;
            }
        }
    }
}
