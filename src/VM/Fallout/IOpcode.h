#pragma once

#include <memory>
#include <string>

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            class IContext;

            class IOpcode
            {
                public:
                    virtual ~IOpcode() = default;
                    virtual void applyTo(std::shared_ptr<IContext>& context) = 0;
                    virtual int number() = 0;
                    virtual std::string name() = 0;
                    virtual std::string notes() = 0;
            };
        }
    }
}
