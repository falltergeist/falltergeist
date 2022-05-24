// Project includes
#include "../../VM/Handler/Opcode8107Handler.h"
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
            Opcode8107::Opcode8107(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8107::_run()
            {
                logger->debug() << "[8107] [*] void obj_set_light_level(Object* object, int level, int radius)"
                                        << std::endl;
                auto object = _script->dataStack()->popObject();
                auto level = _script->dataStack()->popInteger();
                auto radius = _script->dataStack()->popInteger();
                if (level > 100 || level < 0) {
                    _warning("obj_set_light_level: level should be 0-100");
                    return;
                }
                if (radius > 8 || radius < 0) {
                    _warning("obj_set_light_level: radius should be 0-8");
                    return;
                }

                unsigned int light = 65536 / 100 * level;
                object->setLightIntensity(light);
                object->setLightRadius(radius);
            }
        }
    }
}
