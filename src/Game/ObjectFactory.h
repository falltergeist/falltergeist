#pragma once

// Project includes
#include "../ILogger.h"

// Third-party includes

// stdlib
#include <memory>

namespace Falltergeist
{
    namespace Game
    {
        class Object;

        class ObjectFactory
        {
            public:
                ObjectFactory(std::shared_ptr<ILogger> logger);
                ~ObjectFactory() = default;
                Object* createObjectByPID(unsigned int PID);
            private:
                std::shared_ptr<ILogger> logger;
        };
    }
}
