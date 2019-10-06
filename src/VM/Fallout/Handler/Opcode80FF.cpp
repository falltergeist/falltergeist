#include "Opcode80FF.h"
#include "Game/CritterObject.h"
#include "Game/Game.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "ResourceManager.h"
#include "State/Location.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "VM/Fallout/Exception.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80FF::applyTo(std::shared_ptr<IContext> context)
            {
                auto elevation = context->dataStack()->pop()->asInteger();
                auto position = context->dataStack()->pop()->asInteger();
                auto critter = std::dynamic_pointer_cast<Game::CritterObject>(context->dataStack()->pop()->asObject());
                if (!critter) {
                    throw Exception("critter_attempt_placement - invalid critter pointer");
                }
                auto hexagon = Game::getInstance()->locationState()->hexagonGrid()->at(position);
                Game::getInstance()->locationState()->moveObjectToHexagon(critter.get(), hexagon);
                critter->setElevation(elevation);
                context->dataStack()->push(1);
            }

            int Opcode80FF::number()
            {
                return 0x80FF;
            }

            std::string Opcode80FF::name()
            {
                return "int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)";
            }

            std::string Opcode80FF::notes()
            {
                return "";
            }
        }
    }
}


