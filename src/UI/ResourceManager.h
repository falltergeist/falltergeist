#pragma once

// Project includes
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        class ResourceManager final : public IResourceManager
        {
            public:
                ResourceManager() = default;

                virtual ~ResourceManager() = default;

                Image* getImage(const std::string &filename) override;

                std::shared_ptr<Graphics::Sprite> getSprite(const std::string &filename) override;
        };
    }
}
