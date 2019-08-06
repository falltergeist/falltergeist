#include "../../VM/Handler/Opcode8143Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8143::Opcode8143(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8143::_run() {
                Logger::debug("SCRIPT") << "[8143] [=] void attack_setup(ObjectPtr who, ObjectPtr victim)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}
