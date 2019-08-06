#include "../../VM/Handler/Opcode8128Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8128::Opcode8128(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8128::_run() {
                Logger::debug("SCRIPT") << "[8128] [=] int combat_is_initialized()" << std::endl;
                _script->dataStack()->push(0);
            }
        }
    }
}
