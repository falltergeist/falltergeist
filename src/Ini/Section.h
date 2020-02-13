#pragma once

#include <map>
#include <string>
#include <vector>
#include "../Ini/Value.h"

namespace Falltergeist
{
    namespace Ini
    {
        class Section
        {
            public:
                using PropertyMap = std::map<std::string, Value>;
                using PropertyMapConstIterator = PropertyMap::const_iterator;
                using iterator = PropertyMap::iterator;
                using const_iterator = PropertyMap::const_iterator;

                Section(const std::string &name);
                ~Section();

                iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;

                std::string name();

                int propertyInt(const std::string &name, int def);

                double propertyDouble(const std::string &name, double def);

                bool propertyBool(const std::string &name, bool def);

                std::string propertyString(const std::string &name, const std::string &def);

                std::vector<Value> propertyArray(const std::string &name);

                void setPropertyInt(const std::string &name, int value);

                void setPropertyDouble(const std::string &name, double value);

                void setPropertyBool(const std::string &name, bool value);

                void setPropertyString(const std::string &name, const std::string &value);

                void setPropertyArray(const std::string &name, const std::vector<Value> &value);

                bool hasProperty(const std::string &name) const;

            private:

                PropertyMap _properties;
                std::string _name;

                static void _property(PropertyMapConstIterator iter, double &ret, double def);

                static void _property(PropertyMapConstIterator iter, int &ret, int def);

                static void _property(PropertyMapConstIterator iter, bool &ret, bool def);

                static void _property(PropertyMapConstIterator iter, std::string &ret, const std::string &def);

                static void _property(PropertyMapConstIterator iter, std::vector<Value> &ret);

                static bool _hasType(PropertyMapConstIterator iter, Value::Tag tag);
        };
    }
}
