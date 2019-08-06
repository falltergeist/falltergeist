#include "../../VM/Handler/Opcode8149Handler.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8149::Opcode8149(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8149::_run() {
                // TODO: should it return FID of current animation?
                Logger::debug("SCRIPT") << "[8149] [+] int obj_art_fid(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                _script->dataStack()->push(object->FID());
            }
        }
    }
}
