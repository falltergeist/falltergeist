#include "../../Logger.h"
#include "../../VM/Handler/Opcode80A8.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A8::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto dataStack = _script->dataStack();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
                dataStack->popInteger();
            }

            int Opcode80A8::number()
            {
                return 0x80A8;
            }

            std::string Opcode80A8::name()
            {
                return "void set_map_start(int x, int y, int elev, int rot)";
            }

            std::string Opcode80A8::notes()
            {
                return "";
            }
        }
    }
}


