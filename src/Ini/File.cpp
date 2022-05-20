#include <algorithm>
#include "../Exception.h"
#include "../Ini/File.h"

namespace Falltergeist
{
    namespace Ini
    {
        File::File()
        {
        }

        File::~File()
        {
        }

        std::shared_ptr<Section> File::section(const std::string &name)
        {
            auto it = _sections.find(name);
            if (it == _sections.end())
            {
                auto result = std::shared_ptr<Section>(new Section(name));
                _sections[name] = result;
                return result;
            }
            return it->second;
        }

        bool File::hasSection(const std::string &name) const
        {
            return _sections.find(name) != _sections.end();
        }

        std::map<std::string, std::shared_ptr<Section>>* File::sections()
        {
            return &_sections;
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
