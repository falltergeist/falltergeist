#include "../../VM/Handler/Opcode80BFHandler.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BF::Opcode80BF(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80BF::_run()
            {
                logger->debug() << "[80BF] [+] GameDudeObject* dude_obj()" << std::endl;
                auto game = Game::Game::getInstance();
                _script->dataStack()->push(game->player().get());
            }
        }
    }
}