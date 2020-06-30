#include "../../VM/Handler/Opcode80D4Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D4::Opcode80D4(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80D4::_run()
            {
                logger->debug() << "[80D4] [+] int tile_num(GameObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) _error("tile_num - object is NULL");
                _script->dataStack()->push((int) object->hexagon()->number());
            }
        }
    }
}
