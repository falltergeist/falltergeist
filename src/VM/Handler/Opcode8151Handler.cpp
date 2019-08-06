#include "../../VM/Handler/Opcode8151Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8151::Opcode8151(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8151::_run() {
                Logger::debug("SCRIPT") << "[8151] [=] int critter_is_fleeing(void* who)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
