// Project includes
#include "../../VM/Handler/Opcode8113Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8113::Opcode8113(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8113::_run()
            {
                logger->debug()
                    << "[8113] [=] void reg_anim_obj_move_to_tile(void* who, int dest_tile, int delay)"
                    << std::endl
                ;
                _script->dataStack()->popInteger(); // -1
                _script->dataStack()->popInteger();
                _script->dataStack()->popObject();
            }
        }
    }
}
