#include "Game/Object.h"
#include "Opcode8107.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8107::applyTo(std::shared_ptr<IContext> context)
            {
                auto object = context->dataStack()->pop()->asObject();
                auto level = context->dataStack()->pop()->asInteger();
                auto radius = context->dataStack()->pop()->asInteger();
                if (level > 100 || level < 0) {
                    // TODO
                    //_warning("obj_set_light_level: level should be 0-100");
                    return;
                }
                if (radius > 8 || radius < 0) {
                    // TODO
                    //_warning("obj_set_light_level: radius should be 0-8");
                    return;
                }

                unsigned int light = 65536 / 100 * level;
                object->setLightIntensity(light);
                object->setLightRadius(radius);
            }

            int Opcode8107::number()
            {
                return 0x8107;
            }

            std::string Opcode8107::name()
            {
                return "void obj_set_light_level(Object* object, int level, int radius)";
            }

            std::string Opcode8107::notes()
            {
                return "";
            }
        }
    }
}
