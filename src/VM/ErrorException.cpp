// Project includes
#include "../VM/ErrorException.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        ErrorException::ErrorException(const std::string &message) : Exception(message)
        {
        }
    }
}
