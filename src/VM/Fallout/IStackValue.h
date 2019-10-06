#pragma once

#include <memory>
#include <string>

namespace Falltergeist
{
    namespace Game
    {
        class Object;
    }
    namespace VM
    {
        namespace Fallout
        {
            class IStackValue
            {
                public:
                    enum class Type {
                        INTEGER = 1,
                        FLOAT,
                        STRING,
                        OBJECT
                    };
                    virtual int asInteger() const = 0;
                    virtual float asFloat() const = 0;
                    virtual std::string asString() const = 0;
                    virtual Type type() const = 0;
                    virtual std::shared_ptr<Game::Object> asObject() const = 0;
                    virtual std::shared_ptr<IStackValue> add(std::shared_ptr<IStackValue> value) const = 0;
                    virtual std::shared_ptr<IStackValue> sub(std::shared_ptr<IStackValue> value) const = 0;
                    virtual std::shared_ptr<IStackValue> mul(std::shared_ptr<IStackValue> value) const = 0;
                    virtual std::shared_ptr<IStackValue> div(std::shared_ptr<IStackValue> value) const = 0;
            };
        }
    }
}
