#include "../../VM/Handler/Opcode80EFHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80EF::Opcode80EF(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80EF::_run()
            {
                logger->debug()
                    << "[80EF] void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)"
                    << std::endl
                ;
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}


