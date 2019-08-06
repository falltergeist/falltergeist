#include "../../VM/Handler/Opcode8126Handler.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../UI/AnimationQueue.h"
#include "../../VM/Script.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            Opcode8126::Opcode8126(std::shared_ptr<VM::Script> script) : OpcodeHandler(script) {
            }

            void Opcode8126::_run() {
                Logger::debug("SCRIPT") << "[8126] [-] void reg_anim_animate_forever(GameObject* obj , int delay)"
                                        << std::endl;
                /* int delay = */ (void) _script->dataStack()->popInteger();
                /*
                // delay - must be -1
                if (delay != -1)
                {
                    _error("Opcode8126Handler - delay must be -1");
                }
                */
                auto object = _script->dataStack()->popObject();
                auto queue = dynamic_cast<UI::AnimationQueue *>(object->ui());
                if (queue) {
                    queue->stop();
                    queue->setRepeat(true); // forever
                    queue->start();
                }
            }
        }
    }
}
