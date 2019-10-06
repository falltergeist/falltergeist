#include "Opcode811EHandler.h"
#include "Game/Game.h"
#include "State/CritterDialog.h"
#include "State/CritterInteract.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            void Opcode811E::applyTo(std::shared_ptr<IContext> context)
            {
                Logger::debug("SCRIPT") << "[811E] [=] void gSay_Reply(int msg_file_num, int msg_num)" << std::endl;
                auto dialog = dynamic_cast<State::CritterDialog *>(Game::getInstance()->topState());
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
                        if (auto interact = dynamic_cast<State::CritterInteract *>(Game::getInstance()->topState(1))) {
                            interact->playSpeech(speech);
                        }
                    }
                }
            }
        }
    }
}
