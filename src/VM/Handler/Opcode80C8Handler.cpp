// Project includes
#include "../../VM/Handler/Opcode80C8Handler.h"
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
            Opcode80C8::Opcode80C8(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode80C8::_run(VM::Script& script)
            {
                // @TODO: implement
                _logger->debug() << "[80C8] [=] int obj_type(void* obj)" << std::endl;
                auto object = script.dataStack()->popObject();
                Game::Object::Type type = object->type();
                switch (type) {
                    case Game::Object::Type::CRITTER:
                    case Game::Object::Type::DUDE:
                        script.dataStack()->push(1);
                        break;
                    default:
                        script.dataStack()->push((int) type);
                        break;

                }
                //script.dataStack()->push(object);
            }
        }
    }
}


