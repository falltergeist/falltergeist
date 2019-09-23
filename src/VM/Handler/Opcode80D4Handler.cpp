#include "../../VM/Handler/Opcode80D4Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80D4::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80D4] [+] int tile_num(GameObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) _error("tile_num - object is NULL");
                _script->dataStack()->push((int) object->hexagon()->number());
            }
        }
    }
}
