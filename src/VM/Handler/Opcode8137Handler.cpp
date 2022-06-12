// Project includes
#include "../../VM/Handler/Opcode8137Handler.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../State/State.h"
#include "../../VM/HaltException.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8137::Opcode8137(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8137::_run(VM::Script& script)
            {
                int time = script.dataStack()->popInteger(); // original engine ignores time
                _logger->debug()
                    << "[8137] [=] void gfade_in(int time)" << std::endl
                    << "    time = " << time << std::endl
                ;

                auto state = Game::Game::getInstance()->topState();
                // TODO get rid of script dependency
                state->scriptFade(&script, true);
                throw HaltException();
            }
        }
    }
}
