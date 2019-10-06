#include "Opcode80DCHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80DC::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80DC] [=] int obj_can_see_obj(GameObject* src_obj, GameObject* dst_obj)"
                                        << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->popObject();
                _script->dataStack()->push(1);
            }
        }
    }
}


