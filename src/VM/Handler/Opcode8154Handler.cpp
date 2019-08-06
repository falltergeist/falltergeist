#include "../../VM/Handler/Opcode8154Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8154::Opcode8154(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8154::_run() {
                Logger::debug("SCRIPT") << "[8154] [*] void debug(string*)" << std::endl;
                auto value = _script->dataStack()->pop();
                Logger::debug("SCRIPT") << value.toString() << std::endl;
            }
        }
    }
}
