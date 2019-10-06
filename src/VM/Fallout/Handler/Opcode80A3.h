#pragma once

#include "VM/Fallout/IOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                class Opcode80A3 : virtual public IOpcode
                {
                    public:
                        Opcode80A3() = default;
                        void applyTo(std::shared_ptr<IContext>& context) override;
                        int number() override;
                        std::string name() override;
                        std::string notes() override;
                };
            }
        }
    }
}
