// Project includes
#include "../Ini/File.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            File::File()
            {
            }

            File::~File()
            {
            }

            Section& File::section(const std::string &name)
            {
                auto it = _sectionIdxMap.find(name);
                if (it == _sectionIdxMap.end())
                {
                    auto idx = _sections.size();
                    _sections.emplace_back(name);
                    _sectionIdxMap[name] = idx;
                    return _sections.at(idx);
                }
                return _sections.at(it->second);
            }

            Section& File::operator [] (const std::string &name)
            {
                return section(name);
            }

            bool File::hasSection(const std::string &name) const
            {
                return _sectionIdxMap.find(name) != _sectionIdxMap.end();
            }

            const File::Sections& File::sections()
            {
                return _sections;
            }

            File::iterator File::begin()
            {
                return _sections.begin();
            }

            File::const_iterator File::begin() const
            {
                return _sections.begin();
            }

            File::iterator File::end()
            {
                return _sections.end();
            }

            File::const_iterator File::end() const
            {
                return _sections.end();
            }
        }
    }
}
