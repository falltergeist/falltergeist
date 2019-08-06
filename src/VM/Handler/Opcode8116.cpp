#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../Logger.h"
#include "../../State/Location.h"
#include "../../VM/Handler/Opcode8116.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8116::applyTo(std::shared_ptr<IFalloutContext> context)
            {
            //    Logger::debug("SCRIPT")
            //            << "[8116] [+] void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)"
            //            << std::endl;
                auto amount = _script->dataStack()->popInteger();
                auto item = dynamic_cast<Game::ItemObject *>(_script->dataStack()->popObject());
                auto invenObj = _script->dataStack()->popObject();

                if (!item) {
                    _error("add_mult_objs_to_inven - item not instanceof GameItemObject");
                    return;
                }

                item->setAmount(amount);
                // who can be critter or container
                std::vector<Game::ItemObject *> *inven;
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

            int Opcode8116::number()
            {
                return 0x8116;
            }

            std::string Opcode8116::name()
            {
                return "void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)";
            }

            std::string Opcode8116::notes()
            {
                return "";
            }

        }
    }
}
