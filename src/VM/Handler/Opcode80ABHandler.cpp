#include "../../VM/Handler/Opcode80ABHandler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AB::Opcode80AB(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80AB::_run()
            {
                // @TODO: implement
                logger->debug() << "[80AB] [=] int using_skill(GameCritterObject* who, int skill)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
