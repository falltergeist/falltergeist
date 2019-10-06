#include "../../VM/Fallout/Exception.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            Exception::Exception(const std::string &message)
            {
                _message = message;
            }

            Exception::Exception(const Exception &exception) noexcept
            {
                _message = exception._message;
            }

            const char* Exception::what() const noexcept
            {
                return _message.c_str();
            }
        }
    }
}
