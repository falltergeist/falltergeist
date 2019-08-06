#include "../../Game/ArmorItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../Game/Game.h"
#include "../../Game/Object.h"
#include "../../VM/Handler/Opcode8106.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8106::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto where = context->dataStack()->pop()->asInteger();
                auto critter = dynamic_cast<Game::CritterObject *>(context->dataStack()->pop()->asObject());
                switch (where) {
                    case 0: // ARMOR SLOT
                        context->dataStack()->push(critter->armorSlot());
                        break;
                    case 1: // RIGHT HAND SLOT
                        context->dataStack()->push(critter->rightHandSlot());
                        break;
                    case 2: // LEFT HAND SLOT
                        context->dataStack()->push(critter->leftHandSlot());
                        break;
                    case -2: // INVENTORY COUNT
                        context->dataStack()->push((unsigned int) critter->inventory()->size());
                        break;
                    default:
                        // TODO throw exception
                        //_error(std::string("critter_inven_obj - invalid slot: ") + std::to_string(where));
                        break;
                }
            }

            int Opcode8106::number()
            {
                return 0x8106;
            }

            std::string Opcode8106::name()
            {
                return "void* (int) critter_inven_obj(GameCritterObject* critter, int where)";
            }

            std::string Opcode8106::notes()
            {
                return "";
            }
        }
    }
}
