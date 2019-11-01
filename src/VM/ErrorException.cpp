#include "../VM/ErrorException.h"

namespace Falltergeist
{
    namespace VM
    {
        ErrorException::ErrorException(const std::string &message) : Exception(message)
        {
        }
    }
}
