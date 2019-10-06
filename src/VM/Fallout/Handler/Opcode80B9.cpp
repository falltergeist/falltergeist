#include "Opcode80B9.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B9::applyTo(std::shared_ptr<IContext> context)
            {
                // TODO
                //context->setOverrides(true);
            }

            int Opcode80B9::number()
            {
                return 0x80B9;
            }

            std::string Opcode80B9::name()
            {
                return "script_overrides";
            }

            std::string Opcode80B9::notes()
            {
                return "";
            }
        }
    }
}
