#pragma once

#include "VM/Fallout/IOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8130 : virtual public IOpcode
            {
                public:
                    Opcode8130() = default;
                    void applyTo(std::shared_ptr<IContext> context) override;
                    int number() override;
                    std::string name() override;
                    std::string notes() override;
            };
        }
    }
}
