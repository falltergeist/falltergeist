#include "../../../VM/Fallout/Handler/Opcode8003.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                void Opcode8003::applyTo(std::shared_ptr<IContext>& context)
                {
                    // nothing to do here ¯\_(ツ)_/¯
                }

                int Opcode8003::number()
                {
                    return 0x8003;
                }

                std::string Opcode8003::name()
                {
                    return "op_critical_done";
                }

                std::string Opcode8003::notes()
                {
                    return "Unknown";
                }
            }
        }
    }
}
