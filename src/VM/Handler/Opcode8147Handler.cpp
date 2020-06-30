#include "../../VM/Handler/Opcode8147Handler.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8147::Opcode8147(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8147::_run()
            {
                logger->debug()
                    << "[8147] [=] void move_obj_inven_to_obj(void* srcObj, void* destObj)"
                    << std::endl
                ;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
            }
        }
    }
}

