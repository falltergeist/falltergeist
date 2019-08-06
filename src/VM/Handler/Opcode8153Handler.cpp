#include "../../VM/Handler/Opcode8153Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8153::Opcode8153(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8153::_run() {
                Logger::debug("SCRIPT") << "[8153] [=] void terminate_combat()" << std::endl;
            }
        }
    }
}
