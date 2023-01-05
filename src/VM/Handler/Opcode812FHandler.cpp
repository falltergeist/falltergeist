// Project includes
#include "../../VM/Handler/Opcode812FHandler.h"
#include "../../Game/ILockable.h"
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
            Opcode812F::Opcode812F(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode812F::_run(VM::Script& script)
            {
                _logger->debug() << "[812F] [+] void obj_unlock(GameObject* object)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (object) {
                    if (auto lockable = dynamic_cast<Game::ILockable*>(object)) {
                        lockable->unlock();
                    } else {
                        _warning(script, "obj_unlock: object is not Lockable");
                    }
                } else {
                    _warning(script, "obj_unlock: object is null");
                }
            }
        }
    }
}


