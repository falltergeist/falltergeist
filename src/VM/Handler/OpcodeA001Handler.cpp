#include "../../VM/Handler/OpcodeA001Handler.h"
#include "../../Format/Int/File.h"
#include "../../Logger.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            OpcodeA001::OpcodeA001(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void OpcodeA001::_run() {
                union {
                    unsigned int iValue;
                    float fValue;
                }
                        uValue;

                uValue.iValue = _script->script()->readValue();

                // Skip 4 bytes for read float value
                _script->setProgramCounter(_script->programCounter() + 4);
                _script->dataStack()->push(StackValue(uValue.fValue));

                auto &debug = Logger::debug("SCRIPT");
                debug << "[A001] [*] push_d float" << std::endl;
                debug << "    value: " << std::to_string(uValue.fValue) << std::endl;
            }
        }
    }
}
