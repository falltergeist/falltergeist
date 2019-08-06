#include "../../VM/Handler/Opcode8122.h"
#include "../../Game/CritterObject.h"
#include "../../Logger.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8122::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                //auto &debug = Logger::debug("SCRIPT");
                //debug << "[8122] [+] void poison(GameCritterObject* who, int amount)" << std::endl;
                int amount = _script->dataStack()->popInteger();
                //debug << "    amount = " << amount << std::endl;
                auto critter = dynamic_cast<Game::CritterObject *>(_script->dataStack()->popObject());
                if (!critter) {
                    _error("poison - WHO is not critter");
                }
                critter->setPoisonLevel(critter->poisonLevel() + amount);
            }

            int Opcode8122::number()
            {
                return 0x8122;
            }

            std::string Opcode8122::name()
            {
                return "void poison(GameCritterObject* who, int amount)";
            }

            std::string Opcode8122::notes()
            {
                return "";
            }
        }
    }
}
