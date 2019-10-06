#include "Game/Game.h"
#include "Game/Object.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "State/Location.h"
#include "Opcode80A7.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A7::applyTo(std::shared_ptr<IContext> context)
            {
                auto PID = context->dataStack()->pop()->asInteger();
                auto elevation = context->dataStack()->pop()->asInteger();
                auto position = context->dataStack()->pop()->asInteger();
                auto game = Game::getInstance();
                std::shared_ptr<Game::Object> found = nullptr;
                context->dataStack()->push(std::make_shared<StackValue>(found));
                // TODO hexagon grid should contain list of shared ptrs
//                Game::Object *found = nullptr;
//                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects()) {
//                    if (object->PID() == PID && object->elevation() == elevation) {
//                        found = object;
//                        break;
//                    }
//                }
                //context->dataStack()->push(std::make_shared<StackValue>(found));
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


