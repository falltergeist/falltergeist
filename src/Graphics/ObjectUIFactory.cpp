#include "../Graphics/ObjectUIFactory.h"
#include "../ResourceManager.h"
#include "../Format/Frm/File.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../UI/Image.h"

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

            return std::make_unique<UI::Image>(frm, orientation);
        }
    }
}
