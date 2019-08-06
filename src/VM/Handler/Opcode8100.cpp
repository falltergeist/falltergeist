#include "../../VM/Handler/Opcode8100.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8100::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto object = context->dataStack()->pop()->asObject();
                if (!object) {
                    context->dataStack()->push(0);
                } else {
                    context->dataStack()->push(object->PID());
                }
            }

            int Opcode8100::number()
            {
                return 0x8100;
            }

            std::string Opcode8100::name()
            {
                return "in obj_pid(void* obj)";
            }

            std::string Opcode8100::notes()
            {
                return "";
            }
        }
    }
}


