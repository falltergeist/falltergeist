#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80A7 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80A7() = default;
                    void applyTo(std::shared_ptr<IFalloutContext> context) override;
                    int number() override;
                    std::string name() override;
                    std::string notes() override;
            };
        }
    }
}
