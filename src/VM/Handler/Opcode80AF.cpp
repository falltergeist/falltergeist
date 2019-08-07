#include "../../Exception.h"
#include "../../VM/Handler/Opcode80AF.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80AF::applyTo(std::shared_ptr<IFalloutContext> context)
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


