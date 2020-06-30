#pragma once

// C++ standard includes

#include <memory>

// Falltergeist includes

namespace Falltergeist
{
    namespace Game
    {
        class Object;

        class ObjectFactory
        {
            public:
                static ObjectFactory* getInstance();
                std::shared_ptr<Object> createObject(unsigned int PID);

            private:
                ObjectFactory() = default;
                ~ObjectFactory() = default;
                ObjectFactory(ObjectFactory const&) = delete;
                void operator=(ObjectFactory const&) = delete;
        };
    }
}
