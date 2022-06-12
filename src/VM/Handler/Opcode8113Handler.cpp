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
            Opcode8113::Opcode8113(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8113::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8113] [=] void reg_anim_obj_move_to_tile(void* who, int dest_tile, int delay)"
                    << std::endl
                ;
                script.dataStack()->popInteger(); // -1
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
            }
        }
    }
}
