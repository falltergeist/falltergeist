#include "../../VM/Handler/Opcode80A6.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A6::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                context->dataStack()->pop()->asInteger();
                // TODO
                context->dataStack()->push(0);
            }

            int Opcode80A6::number()
            {
                return 0x80A6;
            }

            std::string Opcode80A6::name()
            {
                return "int SkillPoints(int PCStatNum)";
            }

            std::string Opcode80A6::notes()
            {
                return "";
            }
        }
    }
}
