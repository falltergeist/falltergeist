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
        class IFalloutValue
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
                virtual std::shared_ptr<IFalloutValue> add(std::shared_ptr<IFalloutValue> value) const = 0;
                virtual std::shared_ptr<IFalloutValue> sub(std::shared_ptr<IFalloutValue> value) const = 0;
                virtual std::shared_ptr<IFalloutValue> mul(std::shared_ptr<IFalloutValue> value) const = 0;
                virtual std::shared_ptr<IFalloutValue> div(std::shared_ptr<IFalloutValue> value) const = 0;
        };
    }
}
