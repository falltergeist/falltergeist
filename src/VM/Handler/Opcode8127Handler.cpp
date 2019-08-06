#include "../../VM/Handler/Opcode8127Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8127::Opcode8127(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8127::_run() {
                Logger::debug("SCRIPT") << "[8127] [*] void critter_injure(ObjectPtr who, int how)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}
