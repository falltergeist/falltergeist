#include "Opcode80F8Handler.h"
#include "Game/Game.h"
#include "Graphics/Rect.h"
#include "LocationCamera.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F8::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80F8] [=] bool tile_is_visible (int hex)" << std::endl;
                int hexnum = _script->dataStack()->popInteger();
                auto hex = Game::getInstance()->locationState()->hexagonGrid()->at(hexnum);
                bool inrect = Graphics::Rect::inRect(
                        Point(hex->position() - Game::getInstance()->locationState()->camera()->topLeft()),
                        Game::getInstance()->locationState()->camera()->size());
                _script->dataStack()->push(inrect);
            }
        }
    }
}


