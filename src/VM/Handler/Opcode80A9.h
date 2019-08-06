#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80A9 : virtual public IFalloutOpcode
            {
                public:
                int number() override;

                std::string name() override;

                std::string notes() override;

                void applyTo(std::shared_ptr<IFalloutContext> context) override;

                Opcode80A9() = default;
            };
        }
    }
}
