// Project includes
#include "../../VM/Handler/Opcode80A4Handler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A4::Opcode80A4(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80A4::_run(VM::Script& script)
            {
                _logger->debug() << "[80A4] [+] std::string* obj_name(GameCritterObject* who)" << std::endl;
                auto object = script.dataStack()->popObject();
                script.dataStack()->push(object->name());
            }
        }
    }
}


