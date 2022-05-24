// Project includes
#include "../../VM/Handler/Opcode80A3Handler.h"
#include "../../Audio/Mixer.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A3::Opcode80A3(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80A3::_run()
            {
                logger->debug() << "[80A3] [=] void play_sfx(string* p1)" << std::endl;
                auto name = _script->dataStack()->popString();
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/" + name + ".acm");
            }
        }
    }
}


