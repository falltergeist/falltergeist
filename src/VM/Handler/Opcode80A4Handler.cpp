#include "../../VM/Handler/Opcode80A4Handler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80A4::Opcode80A4(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80A4::_run()
            {
                logger->debug() << "[80A4] [+] std::string* obj_name(GameCritterObject* who)" << std::endl;
                auto object = _script->dataStack()->popObject();
                _script->dataStack()->push(object->name());
            }
        }
    }
}


