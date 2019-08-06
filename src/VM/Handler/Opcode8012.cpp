#include "../../VM/Handler/Opcode8012.h"
#include "../../VM/IFalloutContext.h"
#include "../../VM/IFalloutStack.h"
#include "../../VM/IFalloutValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8012::applyTo(std::shared_ptr<IFalloutContext> context)
            {
                auto number = context->dataStack()->pop()->asInteger();
                auto value = context->dataStack()->at(context->dataStack()->stackBase() + number);
                context->dataStack()->push(value);

//                auto &debug = Logger::debug("SCRIPT");
//
//                debug << "[8012] [*] value = op_fetch_global[num]" << std::endl
//                      << "      num: " << number << std::endl;
//                //<< "     type: " << value.typeName() << std::endl
//                //<< "    value: " << value.toString();
//
//                debug << std::endl;
            }

            int Opcode8012::number()
            {
                return 0x8012;
            }

            std::string Opcode8012::name()
            {
                return "mixed op_fetch_global(int number)";
            }

            std::string Opcode8012::notes()
            {
                return "";
            }
        }
    }
}
