#include "Game/ContainerItemObject.h"
#include "Game/DoorSceneryObject.h"
#include "Opcode8130.h"
#include "VM/Fallout/Exception.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8130::applyTo(std::shared_ptr<IContext> context)
            {
                auto object = context->dataStack()->pop()->asObject();
                if (!object) {
                    throw Exception("obj_is_open: object is NULL");
                }

                if (auto door = std::dynamic_pointer_cast<Game::DoorSceneryObject>(object)) {
                    context->dataStack()->push((int)door->opened());
                    return;
                }

                if (auto container = std::dynamic_pointer_cast<Game::ContainerItemObject>(object)) {
                    context->dataStack()->push((int)container->opened());
                    return;
                }

                throw Exception("obj_is_open: object is not openable type!");
            }

            int Opcode8130::number()
            {
                return 0x8130;
            }

            std::string Opcode8130::name()
            {
                return "int obj_is_open(GameObject* object)";
            }

            std::string Opcode8130::notes()
            {
                return "";
            }
        }
    }
}


