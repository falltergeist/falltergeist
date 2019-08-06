#include "../../VM/Handler/Opcode8147Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8147::Opcode8147(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8147::_run() {
                Logger::debug("SCRIPT") << "[8147] [=] void move_obj_inven_to_obj(void* srcObj, void* destObj)"
                                        << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}

