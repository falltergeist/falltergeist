#pragma once

#include <string>
#include <stdarg.h>

namespace Falltergeist {
    namespace Utils {
        class FormattedString final {
        public:
            FormattedString(const std::string format, ...) {
                int n = 0, size=100;
                bool b = false;
                va_list marker = nullptr;

                while (!b) {
                    _actualString.resize(size);
                    va_start(marker, format);
                    n = vsnprintf(_actualString.data(), size, format.c_str(), marker);
                    va_end(marker);
                    if ((n > 0) && (b = (n < size))) {
                        _actualString.resize(n);
                    } else {
                        size *= 2;
                    }
                }
            }

            const std::string& toString() const {
                return _actualString;
            };

        private:
            std::string _actualString;
        };

        std::ostream& operator <<(std::ostream& lhs, const FormattedString& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }
    }
}
