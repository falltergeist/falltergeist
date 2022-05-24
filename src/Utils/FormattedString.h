#pragma once

// Project includes

// Third-party includes

// stdlib
#include <string>
#include <cstdarg>

namespace Falltergeist {
    namespace Utils {
        class FormattedString final {
        public:
            FormattedString(const std::string format, ...);

            const std::string& toString() const;

        private:
            std::string _actualString;
        };

        std::ostream& operator <<(std::ostream& lhs, const FormattedString& rhs);
    }
}
