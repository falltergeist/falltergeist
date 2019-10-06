#include <algorithm>
#include "Opcode80D9Handler.h"
#include "Game/ContainerItemObject.h"
#include "Game/CritterObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80D9::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[80D9] [=] void rm_obj_from_inven(void* who, void* obj)" << std::endl;
                auto item = dynamic_cast<Game::ItemObject *>(_script->dataStack()->popObject());
                auto invenObj = _script->dataStack()->popObject();

                if (!item) {
                    _error("rm_obj_from_inven - item not instanceof GameItemObject");
                    return;
                }

                std::vector<Game::ItemObject *> *inven;
                if (auto critterObj = dynamic_cast<Game::CritterObject *>(invenObj)) {
                    inven = critterObj->inventory();
                } else if (auto contObj = dynamic_cast<Game::ContainerItemObject *>(invenObj)) {
                    inven = contObj->inventory();
                } else {
                    _error("rm_obj_from_inven - wrong WHO parameter");
                    return;
                }
                auto it = std::find(inven->begin(), inven->end(), item);
                if (it != inven->end()) {
                    inven->erase(it);
                }
            }
        }
    }
}


