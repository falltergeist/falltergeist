#pragma once

// Project includes

// Third-party includes

// stdlib
#include <memory>
#include <vector>

namespace Falltergeist
{
    namespace Game
    {
        class Object;
    }

    namespace VM
    {
        class StackValue;

        class Stack
        {
            public:
                Stack();

                ~Stack();

                void push(const StackValue &value);

                void push(unsigned int value);

                void push(int value);

                void push(float value);

                void push(Game::Object *value);

                void push(const std::string &value);

                const StackValue pop();

                int popInteger();

                float popFloat();

                std::string popString();

                Game::Object *popObject();

                bool popLogical();

                const StackValue top();

                std::vector<StackValue> *values();

                size_t size();

                void swap();

            protected:
                std::vector<StackValue> _values;
        };
    }
}
