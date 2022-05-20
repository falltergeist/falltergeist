#include "../../VM/Handler/Opcode814BHandler.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode814B::Opcode814B(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode814B::_run()
            {
                // @TODO
                logger->debug() << "[814B] [*] void* party_member_obj(int pid)" << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->push((Game::Object *) nullptr);
            }
        }
    }
}

