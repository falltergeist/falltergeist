#include "Opcode8126.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "Game/Object.h"
#include "UI/AnimationQueue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8126::applyTo(std::shared_ptr<IContext> context)
            {
                /* int delay = */ (void) context->dataStack()->pop()->asInteger();
                /*
                // delay - must be -1
                if (delay != -1)
                {
                    _error("Opcode8126Handler - delay must be -1");
                }
                */
                auto object = context->dataStack()->pop()->asObject();
                auto queue = dynamic_cast<UI::AnimationQueue *>(object->ui());
                if (queue) {
                    queue->stop();
                    queue->setRepeat(true); // forever
                    queue->start();
                }
            }

            int Opcode8126::number()
            {
                return 0x8126;
            }

            std::string Opcode8126::name()
            {
                return "void reg_anim_animate_forever(GameObject* obj , int delay)";
            }

            std::string Opcode8126::notes()
            {
                return "";
            }
        }
    }
}
