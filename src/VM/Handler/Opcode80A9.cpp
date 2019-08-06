#include "../../VM/Handler/Opcode80A9.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A9::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto dataStack = context->dataStack();

                auto orientation = dataStack->pop()->asInteger();
                auto elevation = dataStack->pop()->asInteger();
                auto y = dataStack->pop()->asInteger();
                auto x = dataStack->pop()->asInteger();
                auto position = y * 200 + x;
                auto game = Game::Game::getInstance();
                auto player = game->player();
                auto hexagon = game->locationState()->hexagonGrid()->at(position);
                Game::getInstance()->locationState()->moveObjectToHexagon(player.get(), hexagon);
                // TODO
                //player->setPosition(position);
                player->setOrientation(orientation);
                player->setElevation(elevation);
                Game::Game::getInstance()->locationState()->centerCameraAtHexagon(player->hexagon());
            }

            int Opcode80A9::number()
            {
                return 0x80A9;
            }

            std::string Opcode80A9::name()
            {
                return "void override_map_start(int x, int y, int elevation, int orientation)";
            }

            std::string Opcode80A9::notes()
            {
                return "";
            }
        }
    }
}
