#pragma once

#include <map>
#include <string>
#include <vector>
#include "../Ini/Value.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Ini
        {
            /**
             * @brief A section in INI file.
             * Contains an ordered map of property names to Value objects.
             */
            class Section
            {
                public:
                    using PropertyMap = std::map<std::string, Value>;
                    using PropertyMapConstIterator = PropertyMap::const_iterator;
                    using iterator = PropertyMap::iterator;
                    using const_iterator = PropertyMap::const_iterator;
                    using PropertyRefs = std::vector<std::reference_wrapper<const Value>>;

                    Section(const std::string &name = "");
                    ~Section();

                    PropertyMap& properties();

                    iterator begin();
                    const_iterator begin() const;
                    iterator end();
                    const_iterator end() const;

                    const std::string& name() const;

                    /**
                     * Checks if property with given name exists in given section.
                     */
                    bool hasProperty(const std::string &name) const;

                    /**
                     * Returns value of property with given name.
                     * @throws std::out_of_range if property doesn't exist
                     */
                    const Value& property(const std::string& name) const;

                    /**
                     * Returns reference to property with given name. If property doesn't exist, it will be created with empty string value.
                     */
                    Value& operator [] (const std::string& name);

                    /**
                     * Sets given value for property with given name
                     */
                    void setProperty(const std::string &name, const Value& value);

                    /**
                     * Returns value of property with given name, or a given default value if such property doesn't exist.
                     */
                    std::string propertyString(const std::string& name, const std::string& def = "") const;

                    /**
                     * Returns value of given property, converted to int.
                     */
                    int propertyInt(const std::string &name, int def) const;

                    /**
                     * Returns value of given property, converted to double.
                     */
                    double propertyDouble(const std::string &name, double def) const;

                    /**
                     * Returns value of given property, converted to bool.
                     */
                    bool propertyBool(const std::string &name, bool def) const;

                    /**
                     * Parse property with given name as array and return it.
                     */
                    Array propertyArray(const std::string &name) const;

                    /**
                     * Returns a vector of references to properties values, that form a list. For example: enc_00, enc_01, enc_02, etc.
                     * @param mask a sprintf-style format of mask. Example: "enc_%02d".
                     * @param start a starting index
                     */
                    PropertyRefs listByMask(const std::string& mask, unsigned int start = 0) const;

                private:

                    PropertyMap _properties;
                    std::string _name;
            };
        }
    }
}
