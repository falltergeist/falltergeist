#include "../../VM/Handler/Opcode8152Handler.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8152::Opcode8152(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8152::_run() {
                Logger::debug("SCRIPT") << "[8152] [=] void op_critter_set_flee_state(critter who, boolean flag)"
                                        << std::endl;
                // @TODO: add implementation
                _script->dataStack()->popLogical();
                _script->dataStack()->popObject();
            }
        }
    }
}
