#include "../../../VM/Fallout/Handler/Opcode8002.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                void Opcode8002::applyTo(std::shared_ptr<IContext>& context)
                {
                    // nothing to do here ¯\_(ツ)_/¯
                }

                int Opcode8002::number()
                {
                    return 0x8002;
                }

                std::string Opcode8002::name()
                {
                    return "op_critical_start";
                }

                std::string Opcode8002::notes()
                {
                    return "Unknown";
                }
            }
        }
    }
}
