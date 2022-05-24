// Project includes
#include "../../VM/Handler/Opcode8116Handler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../State/Location.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8116::Opcode8116(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8116::_run()
            {
                logger->debug()
                    << "[8116] [+] void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)"
                    << std::endl
                ;
                auto amount = _script->dataStack()->popInteger();
                auto item = dynamic_cast<Game::ItemObject *>(_script->dataStack()->popObject());
                auto invenObj = _script->dataStack()->popObject();

                if (!item) {
                    _error("add_mult_objs_to_inven - item not instanceof GameItemObject");
                    return;
                }

                item->setAmount(amount);
                // who can be critter or container
                std::vector<Game::ItemObject *> *inven = nullptr;
                if (auto critterObj = dynamic_cast<Game::CritterObject *>(invenObj)) {
                    inven = critterObj->inventory();
                } else if (auto contObj = dynamic_cast<Game::ContainerItemObject *>(invenObj)) {
                    inven = contObj->inventory();
                } else {
                    _error("add_mult_objs_to_inven - wrong WHO parameter");
                    return;
                }

                inven->push_back(item);

                if (item->hexagon()) {
                    auto location = Game::Game::getInstance()->locationState();
                    if (location) {
                        location->removeObjectFromMap(item);
                    }
                }
            }
        }
    }
}
