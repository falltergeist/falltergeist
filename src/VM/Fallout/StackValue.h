#pragma once

#include "VM/Fallout/IStackValue.h"
#include "Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            class StackValue : public virtual IStackValue
            {
                public:
                    explicit StackValue(int value);
                    explicit StackValue(float value);
                    explicit StackValue(const std::string &value);
                    explicit StackValue(std::shared_ptr<Game::Object> value);
                    virtual ~StackValue() = default;
                    int asInteger() const override;
                    float asFloat() const override;
                    std::string asString() const override;
                    std::shared_ptr<Game::Object> asObject() const override;
                    Type type() const override;
                    std::shared_ptr<IStackValue> add(std::shared_ptr<IStackValue> value) const override;
                    std::shared_ptr<IStackValue> sub(std::shared_ptr<IStackValue> value) const override;
                    std::shared_ptr<IStackValue> mul(std::shared_ptr<IStackValue> value) const override;
                    std::shared_ptr<IStackValue> div(std::shared_ptr<IStackValue> value) const override;

            private:
                    Type _type;
                    int _integerValue;
                    float _floatValue;
                    std::string _stringValue;
                    std::shared_ptr<Game::Object> _objectValue;
            };
        }
    }
}
