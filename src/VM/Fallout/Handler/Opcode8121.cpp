#include "Opcode8121.h"
#include "Game/DudeObject.h"
#include "Game/Game.h"
#include "Logger.h"
#include "State/CritterDialog.h"
#include "VM/Script.h"
#include "VM/StackValue.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode8121::applyTo(std::shared_ptr<IContext> context)
            {
                auto dataStack = _script->dataStack();

                auto reaction = dataStack->popInteger();
                auto function = dataStack->popInteger();
                std::string text;
                if (dataStack->top().type() == StackValue::Type::STRING) {
                    text = dataStack->popString();
                    dataStack->popInteger(); // msg_list
                } else {
                    auto msg_num = dataStack->popInteger();
                    auto msg_file_num = dataStack->popInteger();
                    text = _script->msgMessage(msg_file_num, msg_num);
                }
                auto iq = dataStack->popInteger();
                auto game = Game::getInstance();
                auto dialog = dynamic_cast<State::CritterDialog *>(game->topState());
                if (iq >= 0) {
                    if (game->player()->stat(STAT::INTELLIGENCE) >= iq) {
                        dialog->reactions()->push_back(reaction);
                        dialog->functions()->push_back(function);
                        dialog->addAnswer(text);
                    }
                }
                if (iq < 0) {
                    if (game->player()->stat(STAT::INTELLIGENCE) <= abs(iq)) {
                        dialog->reactions()->push_back(reaction);
                        dialog->functions()->push_back(function);
                        dialog->addAnswer(text);
                    }
                }
            }

            int Opcode8121::number()
            {
                return 0x8121;
            }

            std::string Opcode8121::name()
            {
                return "void giQ_Option(int iq_test, int msg_list, int msg_num, getProcedureByIndex target, int reaction)";
            }

            std::string Opcode8121::notes()
            {
                return "";
            }
        }
    }
}
