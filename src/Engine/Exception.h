#ifndef FALLTERGEIST_EXCEPTION_H
#define FALLTERGEIST_EXCEPTION_H

#include <exception>
#include <string>

namespace Falltergeist
{

class Exception : std::exception
{
private:
    std::string _message;
public:
    Exception(std::string message) throw();
    ~Exception() throw();
    std::string getMessage() throw();
};

}
#endif // FALLTERGEIST_EXCEPTION_H
