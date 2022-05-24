#pragma once

// Project includes
#include "../Ini/Parser.h"
#include "../Ini/Section.h"

// Third-party includes

// stdlib
#include <map>
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            /**
             * @brief A regular INI file.
             */
            class File
            {
                public:
                    using Sections = std::vector<Section>;
                    using iterator = Sections::iterator;
                    using const_iterator = Sections::const_iterator;

                    File();
                    ~File();

                    /**
                     * Returns reference to section with given name. If it's not exist, empty section will be created automatically.
                     */
                    Section& section(const std::string &name);
                    /**
                     * An alias for section().
                     */
                    Section& operator [] (const std::string &name);
                    /**
                     * Checks if section with given name exists or not.
                     */
                    bool hasSection(const std::string &name) const;
                    /**
                     * Returns reference to internal vector of sections.
                     */
                    const Sections& sections();

                    iterator begin();
                    const_iterator begin() const;
                    iterator end();
                    const_iterator end() const;

                private:
                    Sections _sections;
                    std::map<std::string, size_t> _sectionIdxMap;
            };
        }
    }
}
