// Project includes
#include "../../VM/Handler/Opcode810CHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode810C::Opcode810C(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode810C::_run()
            {
                int direction = _script->dataStack()->popInteger();
                int animation = _script->dataStack()->popInteger();
                auto object = static_cast<Game::Object *>(_script->dataStack()->popObject());

                logger->debug()
                    << "[810C] [*] void anim(GameCritterObject* who, int animation, int direction)"
                    << std::endl
                    << "    direction = 0x" << std::hex << direction << std::endl
                    << "    animation = 0x" << std::hex << animation << std::endl
                ;
                switch (animation) {
                    case 1000: // ANIMATE_ROTATION. direction is orientation
                    {
                        object->setOrientation(direction);
                        //critter->setActionAnimation("aa");
                        break;
                    }
                    case 1010: // ANIMATE_SET_FRAME. direction is frame number
                    {
                        _warning("op_anim - unimplemented ANIMATE_SET_FRAME");
                        break;
                    }
                    default: //  set animation? direction is forward/backward
                    {
                        _warning("op_anim - unimplemented animation: " + std::to_string(animation));
                        break;
                    }
                }
            }
        }
    }
}
