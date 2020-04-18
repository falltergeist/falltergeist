#include "../Graphics/Sprite.h"
#include "../UI/Image.h"
#include "../UI/ResourceManager.h"

namespace Falltergeist
{
    namespace UI
    {
        std::unique_ptr<Image> ResourceManager::getImage(const std::string &filename)
        {
            return std::make_unique<Image>(std::make_unique<Graphics::Sprite>(filename));
        }

        std::shared_ptr<Graphics::Sprite> ResourceManager::getSprite(const std::string &filename)
        {
            return std::make_shared<Graphics::Sprite>(filename);
        }
    }
}
