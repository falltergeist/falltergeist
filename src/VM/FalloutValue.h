#pragma once

#include "../VM/IFalloutValue.h"
#include "../Game/Object.h"

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
                explicit FalloutValue(std::shared_ptr<Game::Object> value);
                virtual ~FalloutValue() = default;
                int asInteger() const override;
                float asFloat() const override;
                std::string asString() const override;
                std::shared_ptr<Game::Object> asObject() const override;
                Type type() const override;
                std::shared_ptr<IFalloutValue> add(std::shared_ptr<IFalloutValue> value) const override;
                std::shared_ptr<IFalloutValue> sub(std::shared_ptr<IFalloutValue> value) const override;
                std::shared_ptr<IFalloutValue> mul(std::shared_ptr<IFalloutValue> value) const override;
                std::shared_ptr<IFalloutValue> div(std::shared_ptr<IFalloutValue> value) const override;

        private:
                Type _type;
                int _integerValue;
                float _floatValue;
                std::string _stringValue;
                std::shared_ptr<Game::Object> _objectValue;
        };
    }
}
