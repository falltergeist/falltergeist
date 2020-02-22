#pragma once

#include <memory>

namespace Falltergeist
{
    namespace UI
    {
        class Image;

        class IResourceManager
        {
            public:
                virtual ~IResourceManager() = default;

                // TODO replace with smart pointer
                virtual Image* getImage(const std::string &filename) = 0;
        };
    }
}
