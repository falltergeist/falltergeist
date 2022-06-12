// Project includes
#include "../../VM/Handler/Opcode80EFHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80EF::Opcode80EF(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80EF::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[80EF] void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)"
                    << std::endl
                ;
                script.dataStack()->popInteger();
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
            }
        }
    }
}


