#pragma once

#include "../VM/IFalloutStack.h"

namespace Falltergeist
{
    namespace VM
    {
        class FalloutStack : public virtual IFalloutStack
        {
            public:
                virtual ~FalloutStack() = default;
                void push(std::shared_ptr<IFalloutValue> value) override;
                void push(int value) override;
                std::shared_ptr<IFalloutValue> at(unsigned int offset) override;
                std::shared_ptr<IFalloutValue> pop() override;
                std::shared_ptr<IFalloutValue> top() override;
                void clear() override;
                unsigned int size() override;
                void swap() override;

            private:
                std::vector<std::shared_ptr<IFalloutValue>> _values;
        };
    }
}
