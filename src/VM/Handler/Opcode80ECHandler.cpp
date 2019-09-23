#include "../../VM/Handler/Opcode80ECHandler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80EC::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80EC] [=] int elevation(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("elevation - object is NULL");
                }
                _script->dataStack()->push(object->elevation());
            }
        }
    }
}
