#pragma once

#include <string>

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            class IProcedure
            {
                public:
                    virtual uint32_t flags() const = 0;

                    virtual uint32_t delay() const = 0;

                    virtual uint32_t conditionOffset() const = 0;

                    virtual uint32_t bodyOffset() const = 0;

                    virtual uint32_t argumentsCounter() = 0;

                    virtual std::string name() const = 0;

                    virtual bool isTimed() = 0;

                    virtual bool isConditional() = 0;

                    virtual bool isImported() = 0;

                    virtual bool isExported() = 0;

                    virtual bool isCritical() = 0;

                    virtual bool isPure() = 0;

                    virtual bool isInline() = 0;
            };
        }
    }
}
