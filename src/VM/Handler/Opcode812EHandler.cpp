// Project includes
#include "../../VM/Handler/Opcode812EHandler.h"
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
            Opcode812E::Opcode812E(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode812E::_run(VM::Script& script)
            {
                auto &debug = _logger->debug() << "[812E] [+] void obj_lock(GameObject* object)" << std::endl;
                auto object = script.dataStack()->popObject();
                if (object) {
                    if (auto lockable = dynamic_cast<Game::ILockable*>(object)) {
                        lockable->lock();
                    } else {
                        _warning(script, "obj_lock: object is not Lockable");
                    }
                } else {
                    _warning(script, "obj_lock: object is null");
                }
            }
        }
    }
}
