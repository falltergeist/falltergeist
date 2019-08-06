#include "../../VM/Handler/Opcode8139Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8139::Opcode8139(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8139::_run() {
                Logger::debug("SCRIPT") << "[8139] [=] int item_caps_adjust(void* obj, int amount)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}


