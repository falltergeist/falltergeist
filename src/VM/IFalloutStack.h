#pragma once

#include <memory>
#include <vector>

namespace Falltergeist
{
    namespace VM
    {
        class IFalloutValue;

        class IFalloutStack
        {
            public:
                virtual void push(std::shared_ptr<IFalloutValue> value) = 0;
                virtual void push(int value) = 0;
                virtual std::shared_ptr<IFalloutValue> at(unsigned int offset) = 0;
                virtual std::shared_ptr<IFalloutValue> pop() = 0;
                virtual std::shared_ptr<IFalloutValue> top() = 0;
                virtual void clear() = 0;
                virtual unsigned int size() = 0;
                virtual void swap() = 0;
                virtual int stackBase() = 0;
                virtual void rememberStackBase() = 0;
        };
    }
}
