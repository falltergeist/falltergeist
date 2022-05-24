// Project includes
#include "../../VM/Handler/Opcode80DCHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80DC::Opcode80DC(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80DC::_run()
            {
                logger->debug()
                    << "[80DC] [=] int obj_can_see_obj(GameObject* src_obj, GameObject* dst_obj)"
                    << std::endl
                ;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
                _script->dataStack()->push(1);
            }
        }
    }
}


