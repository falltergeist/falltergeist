#include "../State/CritterDialogReview.h"
#include "../Game/Game.h"
#include "../Game/DudeObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Size.h"
#include "../State/CritterInteract.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/TextAreaList.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        CritterDialogReview::CritterDialogReview(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse
        ) : State(mouse), _resourceManager(resourceManager) {
            _resourceManager = resourceManager;
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        void CritterDialogReview::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(false);

            auto background = _resourceManager->getImage("art/intrface/review.frm");
            Graphics::Point backgroundPos = Graphics::Point((Game::Game::getInstance()->renderer()->size() - background->size()) / 2);
            background->setPosition(backgroundPos);

            // Interface buttons
            auto doneButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_DONE_BUTTON, backgroundPos + Graphics::Point(500, 398));
            doneButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onDoneButtonClick, this, std::placeholders::_1));

            auto upButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_BIG_UP_ARROW, backgroundPos + Graphics::Point(476, 154));
            upButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onUpButtonClick, this, std::placeholders::_1));

            auto downButton = _imageButtonFactory->getByType(ImageButtonType::DIALOG_BIG_DOWN_ARROW, backgroundPos + Graphics::Point(476, 192));
            downButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onDownButtonClick, this, std::placeholders::_1));

            addUI(background);
            addUI(doneButton);
            addUI(upButton);
            addUI(downButton);
            auto list = new UI::TextAreaList(Graphics::Point(88,76));
            list->setSize(Graphics::Size(340, 340));
            addUI("list",list);
        }

        void CritterDialogReview::onStateActivate(Event::State *event) {
            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->scrollTo(0);
        }

        void CritterDialogReview::onDoneButtonClick(Event::Mouse* event)
        {
            if (auto interact = dynamic_cast<CritterInteract*>(Game::Game::getInstance()->topState(1)))
            {
                interact->switchSubState(CritterInteract::SubState::DIALOG);
            }
        }

        void CritterDialogReview::onUpButtonClick(Event::Mouse *event)
        {
            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->scrollUp(4);
        }

        void CritterDialogReview::onDownButtonClick(Event::Mouse *event)
        {
            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->scrollDown(4);
        }

        void CritterDialogReview::setCritterName(const std::string &value)
        {
            _critterName = value;
        }

        void CritterDialogReview::addAnswer(const std::string &value)
        {
            auto dudeName = new UI::TextArea(0, 0);
            dudeName->setWidth(340);
            dudeName->setWordWrap(true);
            dudeName->setFont("font1.aaf", {0xa0,0xa0, 0xa0, 0xff});
            dudeName->setText(Game::Game::getInstance()->player()->name()+":");

            auto answer = new UI::TextArea(0, 0);
            answer->setWidth(316);
            answer->setOffset(Graphics::Point(26, 0));
            answer->setWordWrap(true);
            answer->setFont("font1.aaf", {0x74,0x74, 0x74, 0xff});
            answer->setText(value);

            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->addArea(std::unique_ptr<UI::TextArea>(dudeName));
            list->addArea(std::unique_ptr<UI::TextArea>(answer));
        }

        void CritterDialogReview::addQuestion(const std::string &value)
        {
            auto crName = new UI::TextArea(0, 0);
            crName->setWidth(340);
            crName->setWordWrap(true);
            crName->setFont("font1.aaf", {0x3f,0xf8, 0x00, 0xff});
            crName->setText(_critterName + ":");

            auto question = new UI::TextArea(0, 0);
            question->setWidth(316);
            question->setOffset(Graphics::Point(26, 0));
            question->setWordWrap(true);
            question->setFont("font1.aaf", {0x00,0xa4, 0x00, 0xff});
            question->setText(value);

            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->addArea(std::unique_ptr<UI::TextArea>(crName));
            list->addArea(std::unique_ptr<UI::TextArea>(question));
        }
    }
}
