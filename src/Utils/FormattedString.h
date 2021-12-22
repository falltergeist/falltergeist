#pragma once

#include <string>
#include <stdarg.h>

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
