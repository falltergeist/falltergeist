#include "Game/CritterObject.h"
#include "Opcode810C.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode810C::applyTo(std::shared_ptr<IContext> context)
            {
                int direction = context->dataStack()->pop()->asInteger();
                int animation = context->dataStack()->pop()->asInteger();
                auto object = std::dynamic_pointer_cast<Game::Object>(context->dataStack()->pop()->asObject());

                switch (animation) {
                    case 1000: // ANIMATE_ROTATION. direction is orientation
                    {
                        object->setOrientation(direction);
                        //critter->setActionAnimation("aa");
                        break;
                    }
                    case 1010: // ANIMATE_SET_FRAME. direction is frame number
                    {
                        //_warning("op_anim - unimplemented ANIMATE_SET_FRAME");
                        break;
                    }
                    default: //  set animation? direction is forward/backward
                    {
                        //_warning("op_anim - unimplemented animation: " + std::to_string(animation));
                        break;
                    }
                }
            }

            int Opcode810C::number()
            {
                return 0x810C;
            }

            std::string Opcode810C::name()
            {
                return "void anim(GameCritterObject* who, int animation, int direction)";
            }

            std::string Opcode810C::notes()
            {
                return "";
            }
        }
    }
}
