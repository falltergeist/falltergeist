#include "Exception.h"

namespace Falltergeist
{

Exception::Exception(std::string message) throw()
{
    _message = message;
}

Exception::~Exception() throw()
{
}

std::string Exception::getMessage() throw()
{
    return _message;
}

}

