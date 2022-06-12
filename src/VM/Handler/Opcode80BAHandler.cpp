// Project includes
#include "../../VM/Handler/Opcode80BAHandler.h"
#include "../../Game/ContainerItemObject.h"
#include "../../Game/CritterObject.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80BA::Opcode80BA(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80BA::_run(VM::Script& script)
            {
                _logger->debug() << "[80BA] [+] int obj_is_carrying_obj_pid(GameObject* object, int PID)" << std::endl;
                auto PID = script.dataStack()->popInteger();
                auto object = script.dataStack()->popObject();

                int amount = 0;
                auto critter = dynamic_cast<Game::CritterObject *>(object);
                auto container = dynamic_cast<Game::ContainerItemObject *>(object);
                if (critter) {
                    for (auto object : *critter->inventory()) {
                        if (object->PID() == PID) {
                            amount += object->amount();
                        }
                    }
                } else if (container) {
                    for (auto object : *container->inventory()) {
                        if (object->PID() == PID) {
                            amount += object->amount();
                        }
                    }
                } else {
                    _error("obj_is_carrying_obj_pid - invalid object type");
                }
                script.dataStack()->push(amount);
            }
        }
    }
}
