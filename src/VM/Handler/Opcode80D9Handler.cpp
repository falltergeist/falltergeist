// Project includes
#include "../../VM/Handler/Opcode80D9Handler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib
#include <algorithm>

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80D9::Opcode80D9(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80D9::_run(VM::Script& script)
            {
                _logger->debug() << "[80D9] [=] void rm_obj_from_inven(void* who, void* obj)" << std::endl;
                auto item = dynamic_cast<Game::ItemObject *>(script.dataStack()->popObject());
                auto invenObj = script.dataStack()->popObject();

                if (!item) {
                    _error("rm_obj_from_inven - item not instanceof GameItemObject");
                    return;
                }

                std::vector<Game::ItemObject *> *inven = nullptr;
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


