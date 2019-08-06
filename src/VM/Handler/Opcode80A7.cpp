#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Handler/Opcode80A7.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A7::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto PID = _script->dataStack()->popInteger();
                auto elevation = _script->dataStack()->popInteger();
                auto position = _script->dataStack()->popInteger();
                auto game = Game::getInstance();
                Game::Object *found = nullptr;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects()) {
                    if (object->PID() == PID && object->elevation() == elevation) {
                        found = object;
                        break;
                    }
                }
                _script->dataStack()->push(found);
            }

            int Opcode80A7::number()
            {
                return 0x80A7;
            }

            std::string Opcode80A7::name()
            {
                return "GameObject* tile_contains_pid_obj(int position, int elevation, int PID)";
            }

            std::string Opcode80A7::notes()
            {
                return "";
            }
        }
    }
}


