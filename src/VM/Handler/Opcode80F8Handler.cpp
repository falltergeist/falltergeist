#include "../../VM/Handler/Opcode80F8Handler.h"
#include "../../Game/Game.h"
#include "../../Graphics/Rect.h"
#include "../../LocationCamera.h"
#include "../../PathFinding/Hexagon.h"
#include "../../PathFinding/HexagonGrid.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            using Point = Graphics::Point;

            Opcode80F8::Opcode80F8(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80F8::_run()
            {
                logger->debug() << "[80F8] [=] bool tile_is_visible (int hex)" << std::endl;
                int hexnum = _script->dataStack()->popInteger();
                auto hex = Game::Game::getInstance()->locationState()->hexagonGrid()->at(hexnum);
                bool inrect = Graphics::Rect::inRect(
                        Point(hex->position() - Game::Game::getInstance()->locationState()->camera()->topLeft()),
                        Game::Game::getInstance()->locationState()->camera()->size());
                _script->dataStack()->push(inrect);
            }
        }
    }
}


