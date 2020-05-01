#include "../../Game/Helper/EggHelper.h"
#include "../../Game/Object.h"
#include "../../Game/DudeObject.h"
#include "../../PathFinding/Hexagon.h"

namespace Falltergeist
{
    namespace Game
    {
        namespace Helper
        {
            static bool to_right_of(const Point &p1, const Point &p2)
            {
                return (double) (p2.x() - p1.x()) <= ((double) (p2.y() - p1.y()) * (4.0 / 3.0));
            }

            static bool in_front_of(const Point &p1, const Point &p2)
            {
                return (double) (p2.x() - p1.x()) <= ((double) (p2.y() - p1.y()) * -4.0);
            }

            bool EggHelper::isTransparentForEgg(const Object* object, const std::shared_ptr<DudeObject>& dude)
            {
                bool useEggTransparency = false;

                // only walls and scenery are affected by egg
                if (object->type() == Object::Type::WALL || object->type() == Object::Type::SCENERY) {
                    useEggTransparency = (object->trans() == Graphics::TransFlags::Trans::DEFAULT);
                }

                if (!useEggTransparency) {
                    return false;
                }

                // calculate if dude egg intersects with object
                Hexagon *dudeHex;
                if (dude->movementQueue()->size()) {
                    dudeHex = dude->movementQueue()->back();
                } else {
                    dudeHex = dude->hexagon();
                }

                auto objPos = object->hexagon()->position();
                auto dudePos = dudeHex->position();

                bool noBlockTrans = false;
                bool transparent;

                switch (object->lightOrientation()) {
                    case Orientation::EW:
                    case Orientation::WC:
                        transparent = in_front_of(objPos, dudePos);
                        noBlockTrans = to_right_of(objPos, dudePos);
                        break;
                    case Orientation::NC:
                        transparent = (to_right_of(dudePos, objPos) | in_front_of(objPos, dudePos));
                        break;
                    case Orientation::SC:
                        transparent = (in_front_of(objPos, dudePos) && to_right_of(dudePos, objPos));
                        break;
                    default:
                        transparent = to_right_of(dudePos, objPos);
                        noBlockTrans = in_front_of(dudePos, objPos);
                        break;
                }

                return (noBlockTrans && object->wallTransEnd())
                       ? false
                       : transparent;
            }
        }
    }
}
