#include "../../VM/Handler/OpcodeC001Handler.h"
#include "../../Format/Int/File.h"
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            OpcodeC001::OpcodeC001(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void OpcodeC001::_run() {
                int value = _script->script()->readValue();

                // Skip 4 bytes for readed integer value
                _script->setProgramCounter(_script->programCounter() + 4);
                _script->dataStack()->push(StackValue(value));

                auto &debug = Logger::debug("SCRIPT");
                debug << "[C001] [*] push_d integer" << std::endl;
                debug << "    value: " << std::to_string(value) << std::endl;
            }
        }
    }
}
