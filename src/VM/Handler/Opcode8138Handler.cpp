#include "../../VM/Handler/Opcode8138Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8138::Opcode8138(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8138::_run() {
                Logger::debug("SCRIPT") << "[8138] [=] int item_caps_total(void* obj)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
