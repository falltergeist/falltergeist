#pragma once

#include "VM/Fallout/IStack.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            class Stack : public virtual IStack
            {
                public:
                    virtual ~Stack() = default;
                    void push(std::shared_ptr<IStackValue> value) override;
                    void push(int value) override;
                    std::shared_ptr<IStackValue> at(unsigned int offset) override;
                    std::shared_ptr<IStackValue> pop() override;
                    std::shared_ptr<IStackValue> top() override;
                    void clear() override;
                    unsigned int size() override;
                    void swap() override;

                private:
                    std::vector<std::shared_ptr<IStackValue>> _values;
            };
        }
    }
}
