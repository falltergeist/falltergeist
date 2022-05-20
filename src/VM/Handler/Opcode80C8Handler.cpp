#include "../../VM/Handler/Opcode80C8Handler.h"
#include "../../Game/Object.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80C8::Opcode80C8(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80C8::_run()
            {
                // @TODO: implement
                logger->debug() << "[80C8] [=] int obj_type(void* obj)" << std::endl;
                auto object = _script->dataStack()->popObject();
                Game::Object::Type type = object->type();
                switch (type) {
                    case Game::Object::Type::CRITTER:
                    case Game::Object::Type::DUDE:
                        _script->dataStack()->push(1);
                        break;
                    default:
                        _script->dataStack()->push((int) type);
                        break;

                }
                //_script->dataStack()->push(object);
            }
        }
    }
}


