#pragma once

#include "../Exception.h"

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
