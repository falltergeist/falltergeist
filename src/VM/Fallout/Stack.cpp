#include "VM/Fallout/Exception.h"
#include "VM/Fallout/Stack.h"
#include "VM/Fallout/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            void Stack::push(std::shared_ptr<IStackValue> value)
            {
                _values.push_back(value);
            }

            void Stack::push(int value)
            {
                _values.push_back(std::make_shared<StackValue>(value));
            }

            std::shared_ptr<IStackValue> Stack::at(unsigned int offset)
            {
                return _values.at(offset);
            }

            std::shared_ptr<IStackValue> Stack::pop()
            {
                if (_values.size() == 0) {
                    throw Exception("FalloutStack::pop() - stack is empty");
                }
                auto value = _values.back();
                _values.pop_back();
                return value;
            }

            std::shared_ptr<IStackValue> Stack::top()
            {
                return _values.back();
            }

            void Stack::clear()
            {
                _values.clear();
            }

            unsigned int Stack::size()
            {
                return _values.size();
            }

            void Stack::swap()
            {
                if (_values.size() < 2) {
                    throw Exception("FalloutStack::swap() - stack size is lesser than 2");
                }

                auto value1 = _values.back();
                _values.pop_back();
                auto value2 = _values.back();
                _values.pop_back();
                _values.push_back(value1);
                _values.push_back(value2);
            }
        }
    }
}
