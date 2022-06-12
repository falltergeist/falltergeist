// Project includes
#include "../../Format/Dat/Item.h"

// Third-party includes

// stdlib
#include <algorithm>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            Item& Item::setFilename(const std::string& filename)
            {
                _filename = filename;

                // convert to lowercase and replace slashes
                std::replace(_filename.begin(),_filename.end(),'\\','/');
                std::transform(_filename.begin(),_filename.end(),_filename.begin(), ::tolower);
                return *this;
            }

            const std::string& Item::filename() const
            {
                return _filename;
            }
        }
    }
}
