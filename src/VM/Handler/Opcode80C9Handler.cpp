// Project includes
#include "../../VM/Handler/Opcode80C9Handler.h"
#include "../../Game/AmmoItemObject.h"
#include "../../Game/ArmorItemObject.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/DrugItemObject.h"
#include "../../Game/Game.h"
#include "../../Game/KeyItemObject.h"
#include "../../Game/MiscItemObject.h"
#include "../../Game/Object.h"
#include "../../Game/WeaponItemObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C9::Opcode80C9(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C9::_run()
            {
                logger->debug() << "[80C9] [+] int obj_item_subtype(GameItemObject* object)" << std::endl;
                auto object = _script->dataStack()->popObject();
                if (dynamic_cast<Game::ArmorItemObject *>(object)) {
                    _script->dataStack()->push(0);
                } else if (dynamic_cast<Game::ContainerItemObject *>(object)) {
                    _script->dataStack()->push(1);
                } else if (dynamic_cast<Game::DrugItemObject *>(object)) {
                    _script->dataStack()->push(2);
                } else if (dynamic_cast<Game::WeaponItemObject *>(object)) {
                    _script->dataStack()->push(3);
                } else if (dynamic_cast<Game::AmmoItemObject *>(object)) {
                    _script->dataStack()->push(4);
                } else if (dynamic_cast<Game::MiscItemObject *>(object)) {
                    _script->dataStack()->push(5);
                } else if (dynamic_cast<Game::KeyItemObject *>(object)) {
                    _script->dataStack()->push(6);
                } else {
                    _script->dataStack()->push(-1);
                }
            }
        }
    }
}


