#include "../../VM/Handler/Opcode8129Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8129::Opcode8129(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8129::_run() {
                Logger::debug("SCRIPT") << "[8129] [=] void gdialog_mod_barter(int modifier)" << std::endl;
                _script->dataStack()->popInteger();
            }
        }
    }
}


