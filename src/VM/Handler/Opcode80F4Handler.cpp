#include "../../VM/Handler/Opcode80F4Handler.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80F4::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[80F4] [=] int destroy_object(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                Game::Game::getInstance()->locationState()->destroyObject(object);
                _script->dataStack()->push(0);
            }
        }
    }
}
