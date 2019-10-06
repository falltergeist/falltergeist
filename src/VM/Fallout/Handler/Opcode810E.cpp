#include "Game/CritterObject.h"
#include "UI/AnimationQueue.h"
#include "Opcode810E.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/Exception.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode810E::applyTo(std::shared_ptr<IContext> context)
            {
                auto arg = context->dataStack()->pop(); // pointer or integer
                auto p1 = context->dataStack()->pop()->asInteger();

                if (p1 == 0x1) { // ANIM_BEGIN
                    // @TODO: implement
                    // auto arg = popDataInteger();
                    // RB_UNRESERVED (1) - unreserved sequence, may not play, if there are no free slots left
                    // RB_RESERVED (2) - reserved sequence, should always play
                    return;
                }

                if (p1 == 0x2) { // ANIM_CLEAR
                    auto object = arg->asObject();
                    if (auto critterObject = std::dynamic_pointer_cast<Game::CritterObject>(object)) {
                        critterObject->stopMovement();
                    } else {
                        auto queue = dynamic_cast<UI::AnimationQueue *>(object->ui());
                        if (queue) {
                            queue->stop();
                        }
                    }
                    return;
                }

                if (p1 == 0x3) {  // ANIMATION_END
                    // @TODO: implement
                    return;
                }

                throw Exception("reg_anim_func - unsupported mode");
            }

            int Opcode810E::number()
            {
                return 0x810E;
            }

            std::string Opcode810E::name()
            {
                return "void reg_anim_func(int mode, int arg)";
            }

            std::string Opcode810E::notes()
            {
                return "";
            }
        }
    }
}
