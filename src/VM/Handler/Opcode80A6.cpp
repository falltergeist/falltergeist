#include "../../VM/Handler/Opcode80A6.h"
#include "../../VM/Script.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode80A6::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                _script->dataStack()->popInteger();
                _script->dataStack()->push(0);
            }

            int Opcode80A6::number()
            {
                return 0x80A6;
            }

            std::string Opcode80A6::name()
            {
                return "int SkillPoints(int PCStatNum)";
            }

            std::string Opcode80A6::notes()
            {
                return "";
            }
        }
    }
}
