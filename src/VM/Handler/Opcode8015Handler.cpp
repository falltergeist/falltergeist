// Project includes
#include "../../VM/Handler/Opcode8015Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8015::Opcode8015(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8015::_run(VM::Script& script)
            {
                _logger->debug() << "[8015] [*] op_store_external(name, value)" << std::endl;
                std::string name = script.dataStack()->popString();
                auto value = script.dataStack()->pop();
                auto game = Game::Game::getInstance();
                auto EVARS = game->locationState()->EVARS();
                (*EVARS)[name] = value;
            }
        }
    }
}
