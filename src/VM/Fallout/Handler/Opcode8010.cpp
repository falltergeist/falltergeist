#include "../../../VM/Fallout/Handler/Opcode8010.h"
#include "../../../VM/Fallout/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                void Opcode8010::applyTo(std::shared_ptr<IContext>& context)
                {
                    context->stopExecution();
                }

                int Opcode8010::number()
                {
                    return 0x8010;
                }

                std::string Opcode8010::name()
                {
                    return "void op_exit_prog()";
                }

                std::string Opcode8010::notes()
                {
                    return "Unknown";
                }
            }
        }
    }
}
