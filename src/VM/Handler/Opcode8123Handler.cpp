// Project includes
#include "../../VM/Handler/Opcode8123Handler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8123::Opcode8123(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8123::_run(VM::Script& script)
            {
                auto critter = dynamic_cast<Game::CritterObject *>(script.dataStack()->popObject());
                auto value = critter->poisonLevel();
                script.dataStack()->push(value);
                _logger->debug()
                    << "[8123] [+] int value = GetPoison(GameCritterObject* critter)" << std::endl
                    << "    value = " << value << std::endl
                ;
            }
        }
    }
}
