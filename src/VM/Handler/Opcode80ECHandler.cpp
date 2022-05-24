// Project includes
#include "../../VM/Handler/Opcode80ECHandler.h"
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
            Opcode80EC::Opcode80EC(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80EC::_run()
            {
                logger->debug() << "[80EC] [=] int elevation(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (!object) {
                    _error("elevation - object is NULL");
                }
                _script->dataStack()->push(object->elevation());
            }
        }
    }
}
