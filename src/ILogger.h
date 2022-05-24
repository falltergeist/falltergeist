#pragma once

// Project includes

// Third-party includes

// stdlib
#include <iostream>

namespace Falltergeist
{
    class ILogger
    {
        public:
            virtual ~ILogger() = default;
            virtual std::ostream& debug() = 0;
            virtual std::ostream& info() = 0;
            virtual std::ostream& warning() = 0;
            virtual std::ostream& error() = 0;
            virtual std::ostream& critical() = 0;
    };
}
