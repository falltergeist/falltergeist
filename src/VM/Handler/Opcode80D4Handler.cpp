// Project includes
#include "../../VM/Handler/Opcode80D4Handler.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D4::Opcode80D4(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80D4::_run(VM::Script& script)
            {
                _logger->debug() << "[80D4] [+] int tile_num(GameObject* object)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("tile_num - object is NULL");
                }
                script.dataStack()->push((int) object->hexagon()->number());
            }
        }
    }
}
