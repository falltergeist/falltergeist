#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode800D : virtual public IFalloutOpcode
            {
                public:
                    Opcode800D() = default;
                    void applyTo(std::shared_ptr<IFalloutContext> context) override;
                    int number() override;
                    std::string name() override;
                    std::string notes() override;
            };
        }
    }
}
