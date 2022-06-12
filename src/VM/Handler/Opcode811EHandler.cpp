// Project includes
#include "../../VM/Handler/Opcode811EHandler.h"
#include "../../Game/Game.h"
#include "../../State/CritterDialog.h"
#include "../../State/CritterInteract.h"
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
            Opcode811E::Opcode811E(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode811E::_run(VM::Script& script)
            {
                _logger->debug() << "[811E] [=] void gSay_Reply(int msg_file_num, int msg_num)" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog *>(Game::Game::getInstance()->topState());
                dialog->deleteAnswers();
                if (script.dataStack()->top().type() == StackValue::Type::STRING) {
                    auto question = script.dataStack()->popString();
                    dialog->setQuestion(question);
                } else {
                    auto msg_num = script.dataStack()->popInteger();
                    auto msg_file_num = script.dataStack()->popInteger();
                    dialog->setQuestion(script.msgMessage(msg_file_num, msg_num));
                    auto speech = script.msgSpeech(msg_file_num, msg_num);
                    if (speech != "") {
                        if (auto interact = dynamic_cast<State::CritterInteract *>(Game::Game::getInstance()->topState(1))) {
                            interact->playSpeech(speech);
                        }
                    }
                }
            }
        }
    }
}
