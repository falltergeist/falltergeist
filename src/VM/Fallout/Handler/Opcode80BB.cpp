#include "Game/Game.h"
#include "Game/Object.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "ResourceManager.h"
#include "State/Location.h"
#include "Opcode80BB.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80BB::applyTo(std::shared_ptr<IContext> context)
            {
                auto PID = context->dataStack()->pop()->asInteger();
                auto elevation = context->dataStack()->pop()->asInteger();
                auto position = context->dataStack()->pop()->asInteger();
                auto game = Game::getInstance();
                int found = 0;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects()) {
                    if (object->PID() == PID && object->elevation() == elevation) {
                        found = 1;
                    }
                }
                context->dataStack()->push(found);
            }

            int Opcode80BB::number()
            {
                return 0x80BB;
            }

            std::string Opcode80BB::name()
            {
                return "int tile_contains_obj_pid(int position, int elevation, int PID)";
            }

            std::string Opcode80BB::notes()
            {
                return "";
            }
        }
    }
}
