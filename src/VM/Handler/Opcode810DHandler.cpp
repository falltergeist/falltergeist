#include <algorithm>
#include "../../VM/Handler/Opcode810DHandler.h"
#include "../../Game/CritterObject.h"
#include "../../Game/ItemObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode810D::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                Logger::debug("SCRIPT") << "[810D] [=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
                const int pid = _script->dataStack()->popInteger();
                auto who = _script->dataStack()->popObject();
                if (auto critter = dynamic_cast<Game::CritterObject *>((Game::Object *) who)) {
                    auto iterator = std::find_if(critter->inventory()->begin(), critter->inventory()->end(),
                                                 [&](Game::ItemObject *&item) { return item->PID() == pid; });
                    const bool found = iterator != critter->inventory()->end();
                    _script->dataStack()->push(found ? *iterator : nullptr);
                } else {
                    _warning(std::string("obj_carrying_pid_obj: 'who' is not valid GameCritterObject. It is ") +
                             typeid(who).name());
                    _script->dataStack()->push(nullptr);
                }
            }
        }
    }
}
