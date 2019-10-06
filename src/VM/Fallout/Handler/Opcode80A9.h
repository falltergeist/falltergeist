#pragma once

#include "VM/Fallout/IOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80A9 : virtual public IOpcode
            {
                public:
                int number() override;

                std::string name() override;

                std::string notes() override;

                void applyTo(std::shared_ptr<IContext> context) override;

                Opcode80A9() = default;
            };
        }
    }
}
