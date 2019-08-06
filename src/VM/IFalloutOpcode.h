#pragma once

#include <memory>
#include <string>

namespace Falltergeist
{
    namespace VM
    {
        class IFalloutContext;

        class IFalloutOpcode
        {
            public:
                virtual ~IFalloutOpcode() = default;
                virtual int number() = 0;
                virtual std::string name() = 0;
                virtual std::string notes() = 0;
                virtual void applyTo(std::shared_ptr<IFalloutContext> context) = 0;
        };
    }
}
