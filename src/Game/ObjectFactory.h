#pragma once

#include "../Base/Singleton.h"

namespace Falltergeist
{
    namespace Game
    {
        class Object;

        class ObjectFactory
        {
            public:
                static ObjectFactory* getInstance();
                Object* createObject(unsigned int PID);

            private:
                friend class Base::Singleton<ObjectFactory>;

                ObjectFactory() = default;
                ~ObjectFactory() = default;
                ObjectFactory(ObjectFactory const&) = delete;
                void operator=(ObjectFactory const&) = delete;
        };
    }
}
