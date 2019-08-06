#include "../../VM/Handler/Opcode8125Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8125::Opcode8125(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8125::_run() {
                Logger::debug("SCRIPT") << "[8125] [=] void party_remove(void* who)" << std::endl;
                _script->dataStack()->popObject();
            }
        }
    }
}
