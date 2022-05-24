#pragma once

// Project includes
#include "../Exception.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        class ErrorException : public Exception
        {
            public:
                ErrorException(const std::string &message);
        };
    }
}
