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
            Opcode811E::Opcode811E(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode811E::_run()
            {
                logger->debug() << "[811E] [=] void gSay_Reply(int msg_file_num, int msg_num)" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog *>(Game::Game::getInstance()->topState());
                dialog->deleteAnswers();
                if (_script->dataStack()->top().type() == StackValue::Type::STRING) {
                    auto question = _script->dataStack()->popString();
                    dialog->setQuestion(question);
                } else {
                    auto msg_num = _script->dataStack()->popInteger();
                    auto msg_file_num = _script->dataStack()->popInteger();
                    dialog->setQuestion(_script->msgMessage(msg_file_num, msg_num));
                    auto speech = _script->msgSpeech(msg_file_num, msg_num);
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
