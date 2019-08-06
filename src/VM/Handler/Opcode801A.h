#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode801A :  virtual public IFalloutOpcode
            {
                public:
                    Opcode801A() = default;
                    void applyTo(std::shared_ptr<IFalloutContext> context) override;
                    int number() override;
                    std::string name() override;
                    std::string notes() override;
            };
        }
    }
}
