#pragma once

#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            namespace Handler
            {
                class Opcode80A1 : virtual public IOpcode
                {
                    public:
                        Opcode80A1() = default;
                        void applyTo(std::shared_ptr<IContext>& context) override;
                        int number() override;
                        std::string name() override;
                        std::string notes() override;
                };
            }
        }
    }
}
