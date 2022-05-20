#include <functional>
#include "../Ini/Section.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            Section::Section(const std::string &name) : _name(name)
            {
            }

            Section::~Section()
            {
            }

            const std::string& Section::name() const
            {
                return _name;
            }

            Section::PropertyMap& Section::properties()
            {
                return _properties;
            }

            bool Section::hasProperty(const std::string &name) const
            {
                return _properties.find(name) != _properties.end();
            }

            const Value& Section::property(const std::string& name) const
            {
                return _properties.at(name);
            }

            Value& Section::operator [] (const std::string& name)
            {
                return _properties[name];
            }

            void Section::setProperty(const std::string& name, const Value& value)
            {
                _properties[name] = value;
            }

            std::string Section::propertyString(const std::string &name, const std::string &def) const
            {
                PropertyMapConstIterator iter = _properties.find(name);
                if (iter == _properties.end())
                {
                    return def;
                }
                return iter->second.str();
            }

            int Section::propertyInt(const std::string &name, int def) const
            {
                PropertyMapConstIterator iter = _properties.find(name);
                if (iter == _properties.end())
                {
                    return def;
                }
                return iter->second.toInt();
            }

            double Section::propertyDouble(const std::string &name, double def) const
            {
                PropertyMapConstIterator iter = _properties.find(name);
                if (iter == _properties.end())
                {
                    return def;
                }
                return iter->second.toDouble();
            }

            bool Section::propertyBool(const std::string &name, bool def) const
            {
                PropertyMapConstIterator iter = _properties.find(name);
                if (iter == _properties.end())
                {
                    return def;
                }
                return iter->second.toBool();
            }

            Array Section::propertyArray(const std::string& name) const
            {
                PropertyMapConstIterator iter = _properties.find(name);
                if (iter != _properties.end())
                {
                    return iter->second.toArray();
                }
                return Array();
            }

            Section::PropertyRefs Section::listByMask(const std::string& mask, unsigned int start) const
            {
                PropertyRefs vec;
                int i = start;
                char key[100];
                snprintf(key, 100, mask.c_str(), i);
                while (hasProperty(key))
                {
                    vec.push_back(std::cref(property(key)));
                    snprintf(key, 100, mask.c_str(), ++i);
                }
                return vec;
            }

            Section::iterator Section::begin()
            {
                return _properties.begin();
            }

            Section::const_iterator Section::begin() const
            {
                return _properties.begin();
            }

            Section::iterator Section::end()
            {
                return _properties.end();
            }

            Section::const_iterator Section::end() const
            {
                return _properties.end();
            }
        }
    }
}
