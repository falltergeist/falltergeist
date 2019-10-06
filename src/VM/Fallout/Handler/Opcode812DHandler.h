#pragma  once

#include "VM/Fallout/IOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode812D : virtual public IOpcode
            {
                public:
                    Opcode812D() = default;
                    void applyTo(std::shared_ptr<IContext> context) override;
                    int number() override;
                    std::string name() override;
                    std::string notes() override;
            };
        }
    }
}
