#include "../Exception.h"
#include "../VM/FalloutStack.h"
#include "../VM/FalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        void FalloutStack::push(std::shared_ptr<IFalloutValue> value)
        {
            _values.push_back(value);
        }

        void FalloutStack::push(int value)
        {
            _values.push_back(std::make_shared<FalloutValue>(value));
        }

        std::shared_ptr<IFalloutValue> FalloutStack::at(unsigned int offset)
        {
            return _values.at(offset);
        }

        std::shared_ptr<IFalloutValue> FalloutStack::pop()
        {
            if (_values.size() == 0) {
                throw Exception("FalloutStack::pop() - stack is empty");
            }
            auto value = _values.back();
            _values.pop_back();
            return value;
        }

        std::shared_ptr<IFalloutValue> FalloutStack::top()
        {
            return _values.back();
        }

        void FalloutStack::clear()
        {
            _values.clear();
        }

        unsigned int FalloutStack::size()
        {
            return _values.size();
        }

        void FalloutStack::swap()
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
