// Project includes
#include "../../VM/Handler/Opcode814BHandler.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode814B::Opcode814B(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode814B::_run(VM::Script& script)
            {
                // @TODO
                _logger->debug() << "[814B] [*] void* party_member_obj(int pid)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->push((Game::Object *) nullptr);
            }
        }
    }
}

