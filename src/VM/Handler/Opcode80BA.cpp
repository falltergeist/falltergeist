#include "../../Exception.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Handler/Opcode80BA.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BA::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto PID = context->dataStack()->pop()->asInteger();
                auto object = context->dataStack()->pop()->asObject();

                int amount = 0;
                auto critter = std::dynamic_pointer_cast<Game::CritterObject>(object);
                auto container = std::dynamic_pointer_cast<Game::ContainerItemObject>(object);
                if (critter) {
                    for (auto object : *critter->inventory()) {
                        if (object->PID() == PID) amount += object->amount();
                    }
                } else if (container) {
                    for (auto object : *container->inventory()) {
                        if (object->PID() == PID) amount += object->amount();
                    }
                } else {
                    throw Exception("obj_is_carrying_obj_pid - invalid object type");
                }
                context->dataStack()->push((int)amount);
            }

            int Opcode80BA::number()
            {
                return 0x80BA;
            }

            std::string Opcode80BA::name()
            {
                return "int obj_is_carrying_obj_pid(GameObject* object, int PID)";
            }

            std::string Opcode80BA::notes()
            {
                return "";
            }
        }
    }
}
