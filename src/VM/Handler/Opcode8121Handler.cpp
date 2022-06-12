// Project includes
#include "../../VM/Handler/Opcode8121Handler.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../VM/Script.h"
#include "../../VM/StackValue.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8121::Opcode8121(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8121::_run(VM::Script& script)
            {
                _logger->debug()
                    << "[8121] [+] void giQ_Option(int iq_test, int msg_list, int msg_num, procedure target, int reaction)"
                    << std::endl
                ;

                auto dataStack = script.dataStack();

                auto reaction = dataStack->popInteger();
                auto function = dataStack->popInteger();
                std::string text;
                if (dataStack->top().type() == StackValue::Type::STRING) {
                    text = dataStack->popString();
                    dataStack->popInteger(); // msg_list
                } else {
                    auto msg_num = dataStack->popInteger();
                    auto msg_file_num = dataStack->popInteger();
                    text = script.msgMessage(msg_file_num, msg_num);
                }
                auto iq = dataStack->popInteger();
                auto game = Game::Game::getInstance();
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
        }
    }
}
