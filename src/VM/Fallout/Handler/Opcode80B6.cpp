#include "Game/Game.h"
#include "Game/DudeObject.h"
#include "Exception.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "State/Location.h"
#include "Opcode80B6.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B6::applyTo(std::shared_ptr<IContext> context)
            {
                auto elevation = context->dataStack()->pop()->asInteger();
                auto position = context->dataStack()->pop()->asInteger();
                auto object = context->dataStack()->pop()->asObject();
                if (!object) {
                    throw Exception("move_to: object is NULL");
                }
                auto hexagon = Game::getInstance()->locationState()->hexagonGrid()->at(position);
                Game::getInstance()->locationState()->moveObjectToHexagon(object.get(), hexagon);
                object->setElevation(elevation);
                if (object.get() == Game::getInstance()->player().get()) {
                    Game::getInstance()->locationState()->centerCameraAtHexagon(object->hexagon());
                }
                context->dataStack()->push((int)0);
            }

            int Opcode80B6::number()
            {
                return 0x80B6;
            }

            std::string Opcode80B6::name()
            {
                return "int move_to(GameObject* object, int position, int elevation)";
            }

            std::string Opcode80B6::notes()
            {
                return "";
            }
        }
    }
}
