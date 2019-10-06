#include "Game/Game.h"
#include "Game/Object.h"
#include "PathFinding/Hexagon.h"
#include "PathFinding/HexagonGrid.h"
#include "ResourceManager.h"
#include "State/Location.h"
#include "Opcode80B7.h"
#include "VM/Fallout/IContext.h"
#include "VM/Fallout/IStack.h"
#include "VM/Fallout/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80B7::applyTo(std::shared_ptr<IContext> context)
            {
                auto dataStack = context->dataStack();
                auto SID = dataStack->pop()->asInteger();
                auto elevation = dataStack->pop()->asInteger();
                auto position = dataStack->pop()->asInteger();
                auto PID = dataStack->pop()->asInteger();
                auto object = Game::getInstance()->locationState()->addObject(PID, position, elevation);
                if (SID > 0) {
                    auto intFile = ResourceManager::getInstance()->intFileType(SID);
                    if (intFile) {
                        object->setScript(std::make_shared<VM::Script>(intFile, object));
                    }
                }
                if (object->script()) {
                    object->script()->initialize();
                }
                std::shared_ptr<Game::Object> objectPtr(object);
                context->dataStack()->push(std::make_shared<StackValue>(objectPtr));
            }

            int Opcode80B7::number()
            {
                return 0x80B7;
            }

            std::string Opcode80B7::name()
            {
                return "GameObject* create_object_sid(int PID, int position, int elevation, int SID)";
            }

            std::string Opcode80B7::notes()
            {
                return "";
            }
        }
    }
}
