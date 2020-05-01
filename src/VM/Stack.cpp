#include <string>
#include "../Exception.h"
#include "../VM/Stack.h"
#include "../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        Stack::Stack()
        {
        }

        Stack::~Stack()
        {
        }

        void Stack::push(const StackValue &value)
        {
            _values.push_back(value);
        }

        const StackValue Stack::pop()
        {
            if (_values.size() == 0) {
                throw Exception("Stack::pop() - stack is empty");
            }
            auto value = _values.back();
            _values.pop_back();
            return value;
        }

        size_t Stack::size()
        {
            return _values.size();
        }

        void Stack::swap()
        {
            if (_values.size() < 2) {
                throw Exception("Stack::swap() - size is < 2");
            }

            auto value1 = _values.back();
            _values.pop_back();
            auto value2 = _values.back();
            _values.pop_back();
            _values.push_back(value1);
            _values.push_back(value2);
        }

        std::vector<StackValue> *Stack::values()
        {
            return &_values;
        }

        const StackValue Stack::top()
        {
            return _values.back();
        }

        int Stack::popInteger()
        {
            return pop().integerValue();
        }

        void Stack::push(unsigned int value)
        {
            push((int) value);
        }

        void Stack::push(int value)
        {
            push(StackValue(value));
        }

        float Stack::popFloat()
        {
            return pop().floatValue();
        }

        void Stack::push(float value)
        {
            push(StackValue(value));
        }

        Game::Object *Stack::popObject()
        {
            return pop().objectValue();
        }

        void Stack::push(Game::Object *value)
        {
            push(StackValue(value));
        }

        std::string Stack::popString()
        {
            return pop().stringValue();
        }

        void Stack::push(const std::string &value)
        {
            push(StackValue(value));
        }

        bool Stack::popLogical()
        {
            return pop().toBoolean();
        }
    }
}
