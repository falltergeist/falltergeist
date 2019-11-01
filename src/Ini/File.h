#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include "../Ini/Parser.h"
#include "../Ini/Section.h"

namespace Falltergeist
{
    namespace Ini
    {
        class File
        {
            public:
                using iterator = std::map<std::string, std::shared_ptr<Section>>::iterator;
                using const_iterator = std::map<std::string, std::shared_ptr<Section>>::const_iterator;

                File();
                ~File();
                std::shared_ptr<Section> section(const std::string &name);
                std::map<std::string, std::shared_ptr<Section>>* sections();

                iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;

                bool hasSection(const std::string &name) const;

            private:
                std::map<std::string, std::shared_ptr<Section>> _sections;
        };
    }
}
