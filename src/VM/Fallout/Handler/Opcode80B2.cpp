#include "Opcode80B2.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B2::applyTo(std::shared_ptr<IContext> context)
            {
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asInteger();
                context->dataStack()->pop()->asInteger();
            }

            int Opcode80B2::number()
            {
                return 0x80B2;
            }

            std::string Opcode80B2::name()
            {
                return "void mark_area_known(int AREA_MARK_TYPE, int AreaNum, int MARK_STATE)";
            }

            std::string Opcode80B2::notes()
            {
                return "";
            }
        }
    }
}
