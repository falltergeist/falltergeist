// Project includes
#include "../../VM/Handler/Opcode80ABHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80AB::Opcode80AB(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80AB::_run(VM::Script& script) {
                // @TODO: implement
                _logger->debug() << "[80AB] [=] int using_skill(GameCritterObject* who, int skill)" << std::endl;
                script.dataStack()->popInteger();
                script.dataStack()->popObject();
                script.dataStack()->push(0);
            }
        }
    }
}
