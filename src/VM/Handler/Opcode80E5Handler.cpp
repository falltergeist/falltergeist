// Project includes
#include "../../VM/Handler/Opcode80E5Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80E5::Opcode80E5(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80E5::_run()
            {
                logger->debug()
                    << "[80E5] [=] void wm_area_set_pos(int areaIdx, int xPos, int yPos)"
                    << std::endl
                ;
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
            }
        }
    }
}
