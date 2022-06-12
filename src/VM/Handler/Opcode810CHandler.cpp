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
            Opcode810C::Opcode810C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode810C::_run(VM::Script& script)
            {
                int direction = script.dataStack()->popInteger();
                int animation = script.dataStack()->popInteger();
                auto object = static_cast<Game::Object *>(script.dataStack()->popObject());

                _logger->debug()
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
                        _warning(script, "op_anim - unimplemented ANIMATE_SET_FRAME");
                        break;
                    }
                    default: //  set animation? direction is forward/backward
                    {
                        _warning(script, "op_anim - unimplemented animation: " + std::to_string(animation));
                        break;
                    }
                }
            }
        }
    }
}
