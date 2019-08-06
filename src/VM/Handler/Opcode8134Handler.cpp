#include "../../VM/Handler/Opcode8134Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8134::Opcode8134(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8134::_run() {
                Logger::debug("SCRIPT") << "[8134] [=] void game_ui_enable()" << std::endl;
            }
        }
    }
}
