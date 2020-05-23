#include "../Game/SpatialObject.h"
#include "../PathFinding/Hexagon.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        SpatialObject::SpatialObject(unsigned int radius) : Object(), _radius(radius)
        {
        }

        void SpatialObject::spatial_p_proc(const std::shared_ptr<Object> &source)
        {
            if (_script && _script->hasFunction("spatial_p_proc")) {
                _script
                    ->setSourceObject(source)
                    ->call("spatial_p_proc")
                ;
            }
        }

        unsigned int SpatialObject::radius()
        {
            return _radius;
        }
    }
}
