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
            Opcode80EC::Opcode80EC(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80EC::_run(VM::Script& script)
            {
                _logger->debug() << "[80EC] [=] int elevation(void* obj)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (!object) {
                    _error("elevation - object is NULL");
                }
                script.dataStack()->push(object->elevation());
            }
        }
    }
}
