// Project includes
#include "../Graphics/ObjectUIFactory.h"
#include "../ResourceManager.h"
#include "../Format/Frm/File.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        std::unique_ptr<UI::Base> ObjectUIFactory::buildByFID(uint32_t fid, Game::Orientation orientation)
        {
            auto frm = ResourceManager::getInstance()->frmFileType(fid);
            if (!frm) {
                return nullptr;
            }

            if (frm->framesPerDirection() > 1 || frm->directions().size() > 1) {
                auto queue = std::make_unique<UI::AnimationQueue>();
                queue->animations().push_back(
                    std::make_unique<UI::Animation>(
                        ResourceManager::getInstance()->FIDtoFrmName(fid),
                        orientation
                    )
                );
                return queue;
            }

            auto image = std::make_unique<UI::Image>(std::make_unique<Sprite>(frm));
            auto direction = static_cast<unsigned>(orientation);
            if (direction >= frm->directions().size()) {
                //throw Exception("Image::Image(frm, direction) - direction not found: " + std::to_string(direction));
                direction = 0;
            }
            auto& dir = frm->directions().at(direction);
            image->setOffset(Point(
                frm->offsetX(direction) + dir.shiftX(),
                frm->offsetY(direction) + dir.shiftY()
            ));

            return image;
        }
    }
}
