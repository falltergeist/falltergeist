// Project includes
#include "../Ini/File.h"
#include "../Ini/Writer.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Ini
    {
        Writer::Writer(const File &ini) : _ini(ini)
        {
        }

        Writer::~Writer()
        {
        }

        void Writer::write(std::ostream &stream)
        {
            stream << "# This file contains default configuration for the falltergeist engine." << std::endl;
            stream << "# It was autogenerated for you with love by falltergeist." << std::endl << std::endl;

            for (auto &section : _ini) {
                stream << "[" << section.first << "]" << std::endl;

                for (auto &properties : *section.second) {
                    stream << properties.first <<  "=" << properties.second.value() << std::endl;
                }

                stream << std::endl;
            }
        }
    }
}
