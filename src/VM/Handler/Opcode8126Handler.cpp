// Project includes
#include "../../VM/Handler/Opcode8126Handler.h"
#include "../../Game/Object.h"
#include "../../UI/AnimationQueue.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8126::Opcode8126(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8126::_run()
            {
                logger->debug()
                    << "[8126] [-] void reg_anim_animate_forever(GameObject* obj , int delay)"
                    << std::endl
                ;
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
