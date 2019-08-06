#pragma once

#include "../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        class FalloutValue : public virtual IFalloutValue
        {
            public:
                explicit FalloutValue(int value);
                explicit FalloutValue(float value);
                explicit FalloutValue(const std::string &value);
                virtual ~FalloutValue() = default;
                int asInteger() const override;
                float asFloat() const override;
                std::string asString() const override;
                Type type() const override;
                std::shared_ptr<IFalloutValue> add(std::shared_ptr<IFalloutValue> value) const override;

            private:
                Type _type;
                int _integerValue;
                float _floatValue;
                std::string _stringValue;
        };
    }
}
