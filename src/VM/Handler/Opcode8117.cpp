#include "../../Logger.h"
#include "../../VM/Handler/Opcode8117.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8117::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                //Logger::debug("SCRIPT") << "[8117] [=] int rm_mult_objs_from_inven(void* who, void* obj, int count)"
                //                       << std::endl;
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popObject();
                dataStack->popObject();
                dataStack->push(0);
            }

            int Opcode8117::number()
            {
                return 0x8117;
            }

            std::string Opcode8117::name()
            {
                return "int rm_mult_objs_from_inven(void* who, void* obj, int count)";
            }

            std::string Opcode8117::notes()
            {
                return "";
            }
        }
    }
}


