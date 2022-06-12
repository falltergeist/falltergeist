// Project includes
#include "../../VM/Handler/Opcode8106Handler.h"
#include "../../Game/ArmorItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8106::Opcode8106(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8106::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8106] [=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)"
                    << std::endl
                ;
                auto where = script.dataStack()->popInteger();
                auto critter = dynamic_cast<Game::CritterObject *>(script.dataStack()->popObject());
                switch (where) {
                    case 0: // ARMOR SLOT
                        script.dataStack()->push(critter->armorSlot());
                        break;
                    case 1: // RIGHT HAND SLOT
                        script.dataStack()->push(critter->rightHandSlot());
                        break;
                    case 2: // LEFT HAND SLOT
                        script.dataStack()->push(critter->leftHandSlot());
                        break;
                    case -2: // INVENTORY COUNT
                        script.dataStack()->push((unsigned int) critter->inventory()->size());
                        break;
                    default:
                        _error(std::string("critter_inven_obj - invalid slot: ") + std::to_string(where));
                }
            }
        }
    }
}
