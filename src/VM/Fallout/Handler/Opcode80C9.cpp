#include "Opcode80C9.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/IStackValue.h"
#include "Game/AmmoItemObject.h"
#include "Game/ArmorItemObject.h"
#include "Game/ContainerItemObject.h"
#include "Game/DrugItemObject.h"
#include "Game/KeyItemObject.h"
#include "Game/MiscItemObject.h"
#include "Game/WeaponItemObject.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80C9::applyTo(std::shared_ptr<IContext> context)
            {
                auto object = context->dataStack()->pop()->asObject();
                if (std::dynamic_pointer_cast<Game::ArmorItemObject>(object)) {
                    context->dataStack()->push(0);
                } else if (std::dynamic_pointer_cast<Game::ContainerItemObject>(object)) {
                    context->dataStack()->push(1);
                } else if (std::dynamic_pointer_cast<Game::DrugItemObject>(object)) {
                    context->dataStack()->push(2);
                } else if (std::dynamic_pointer_cast<Game::WeaponItemObject>(object)) {
                    context->dataStack()->push(3);
                } else if (std::dynamic_pointer_cast<Game::AmmoItemObject>(object)) {
                    context->dataStack()->push(4);
                } else if (std::dynamic_pointer_cast<Game::MiscItemObject>(object)) {
                    context->dataStack()->push(5);
                } else if (std::dynamic_pointer_cast<Game::KeyItemObject>(object)) {
                    context->dataStack()->push(6);
                } else {
                    context->dataStack()->push(-1);
                }
            }

            int Opcode80C9::number()
            {
                return 0x80C9;
            }

            std::string Opcode80C9::name()
            {
                return "int obj_item_subtype(GameItemObject* object)";
            }

            std::string Opcode80C9::notes()
            {
                return "";
            }
        }
    }
}


