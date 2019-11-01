#include "Exception.h"

namespace Falltergeist
{
    Exception::Exception(const char* message) : _error(message)
    {
    }

    Exception::Exception(const std::string& message) : _error(message.c_str())
    {
    }

    const char* Exception::what() const noexcept
    {
        return _error.what();
    }
}
