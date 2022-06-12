#pragma once

// Project includes

// Third-party includes

// stdlib
#include <memory>

namespace Falltergeist
{
    namespace Graphics
    {
        class Sprite;
    }

    namespace UI
    {
        class Image;

        class IResourceManager
        {
            public:
                virtual ~IResourceManager() = default;

                virtual std::shared_ptr<Image> getImage(const std::string &filename) = 0;

                virtual std::shared_ptr<Graphics::Sprite> getSprite(const std::string &filename) = 0;
        };
    }
}
