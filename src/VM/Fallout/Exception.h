#pragma once

#include <exception>
#include <string>

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            class Exception : virtual public std::exception
            {
                public:
                    explicit Exception(const std::string& message);
                    Exception(const Exception& exception) noexcept;
                    ~Exception() noexcept override = default;
                    const char* what() const noexcept override;

                private:
                    std::string _message;
            };
        }
    }
}
