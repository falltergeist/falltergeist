#include "Opcode80E5Handler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80E5::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80E5] [=] void wm_area_set_pos(int areaIdx, int xPos, int yPos)"
                                        << std::endl;
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
                _script->dataStack()->popInteger();
            }
        }
    }
}
