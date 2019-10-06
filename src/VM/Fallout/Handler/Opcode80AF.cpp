#include "Exception.h"
#include "Opcode80AF.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AF::applyTo(std::shared_ptr<IContext> context)
            {
                auto value = context->dataStack()->pop()->asInteger();
                switch (value) {
                    case 0:
                    case 1:
                        context->dataStack()->push((int)0);
                        break;
                    case 2:
                    case 3:
                        context->dataStack()->push((int)1);
                        break;
                    default:
                        throw Exception("is_success - wrong argument: " + std::to_string(value));
                }
            }

            int Opcode80AF::number()
            {
                return 0x80AF;
            }

            std::string Opcode80AF::name()
            {
                return "int is_success(int val)";
            }

            std::string Opcode80AF::notes()
            {
                return "";
            }
        }
    }
}


