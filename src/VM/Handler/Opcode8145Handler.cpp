// Project includes
#include "../../VM/Handler/Opcode8145Handler.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8145::Opcode8145(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8145::_run()
            {
                logger->debug() << "[8145] [=] void use_obj_on_obj(void* item, void* target)" << std::endl;
                auto selfCritter = dynamic_cast<Game::CritterObject *>(_script->owner());
                if (!selfCritter) {
                    _error("use_obj_on_obj: owner is not a critter!");
                }
                auto target = _script->dataStack()->popObject();
                if (!target) {
                    _error("use_obj_on_obj: target is null");
                }
                auto item = _script->dataStack()->popObject();
                if (!item) {
                    _error("use_obj_on_obj: item is null");
                }
                // @TODO: play animation
                //selfCritter->setActionAnimation("al");
                target->use_obj_on_p_proc(item, selfCritter);

            }
        }
    }
}
