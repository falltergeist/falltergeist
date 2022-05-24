#pragma once

// Project includes

// Third-party includes

// stdlib
#include <ostream>

namespace Falltergeist
{
    namespace Ini
    {
        class File;

        class Writer
        {
            public:
                Writer(const File &ini);
                ~Writer();

                void write(std::ostream &stream);

            private:
                const File &_ini;
        };
    }
}
