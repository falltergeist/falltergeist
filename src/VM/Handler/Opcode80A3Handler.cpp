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
            Opcode80A3::Opcode80A3(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80A3::_run(VM::Script& script)
            {
                _logger->debug() << "[80A3] [=] void play_sfx(string* p1)" << std::endl;
                auto name = script.dataStack()->popString();
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/" + name + ".acm");
            }
        }
    }
}


