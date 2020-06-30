#include "../../VM/Handler/Opcode8106Handler.h"
#include "../../Game/ArmorItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8106::Opcode8106(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8106::_run()
            {
                logger->debug()
                    << "[8106] [=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)"
                    << std::endl
                ;
                auto where = _script->dataStack()->popInteger();
                auto critter = dynamic_cast<Game::CritterObject *>(_script->dataStack()->popObject());
                switch (where) {
                    case 0: // ARMOR SLOT
                        _script->dataStack()->push(critter->armorSlot());
                        break;
                    case 1: // RIGHT HAND SLOT
                        _script->dataStack()->push(critter->rightHandSlot());
                        break;
                    case 2: // LEFT HAND SLOT
                        _script->dataStack()->push(critter->leftHandSlot());
                        break;
                    case -2: // INVENTORY COUNT
                        _script->dataStack()->push((unsigned int) critter->inventory()->size());
                        break;
                    default:
                        _error(std::string("critter_inven_obj - invalid slot: ") + std::to_string(where));
                }
            }
        }
    }
}
