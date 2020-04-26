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
    using Graphics::Size;
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        CritterDialogReview::CritterDialogReview(std::shared_ptr<UI::IResourceManager> _resourceManager) :
            State{},
            resourceManager{std::move(_resourceManager)},
            imageButtonFactory{std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager)}
        {
        }

        void CritterDialogReview::init()
        {
            if (_initialized) {
                return;
            }

            State::init();

            setFullscreen(false);
            setModal(false);

            auto& background = addUI(resourceManager->getImage("art/intrface/review.frm"));
            Point backgroundPos = Point((Game::getInstance()->renderer()->size() - background.size()) / 2);
            background.setPosition(backgroundPos);

            // Interface buttons

            {
                auto& doneButton = addUI(imageButtonFactory->getByType(ImageButtonType::DIALOG_DONE_BUTTON, backgroundPos + Point(500, 398)));
                doneButton.mouseClickHandler().add(std::bind(&CritterDialogReview::onDoneButtonClick, this, std::placeholders::_1));
            }

            {
                auto& upButton = addUI(imageButtonFactory->getByType(ImageButtonType::DIALOG_BIG_UP_ARROW, backgroundPos + Point(476, 154)));
                upButton.mouseClickHandler().add(std::bind(&CritterDialogReview::onUpButtonClick, this, std::placeholders::_1));
            }

            {
                auto& downButton = addUI(imageButtonFactory->getByType(ImageButtonType::DIALOG_BIG_DOWN_ARROW, backgroundPos + Point(476, 192)));
                downButton.mouseClickHandler().add(std::bind(&CritterDialogReview::onDownButtonClick, this, std::placeholders::_1));
            }

            {
                auto& list = makeNamedUI<UI::TextAreaList>("list", Point{88, 76});
                list.setSize(Size(340,340));
            }
        }

        void CritterDialogReview::onStateActivate(Event::State *event)
        {
            getUI<UI::TextAreaList>("list")->scrollTo(0);
        }


        void CritterDialogReview::onDoneButtonClick(Event::Mouse* event)
        {
            if (auto interact = dynamic_cast<CritterInteract*>(&Game::getInstance()->topState(1)))
            {
                interact->switchSubState(CritterInteract::SubState::DIALOG);
            }
        }

        void CritterDialogReview::onUpButtonClick(Event::Mouse *event)
        {
            getUI<UI::TextAreaList>("list")->scrollUp(4);
        }

        void CritterDialogReview::onDownButtonClick(Event::Mouse *event)
        {
            getUI<UI::TextAreaList>("list")->scrollDown(4);
        }

        void CritterDialogReview::setCritterName(const std::string &value)
        {
            _critterName = value;
        }

        void CritterDialogReview::addAnswer(const std::string &value)
        {
            auto dudeName = std::make_unique<UI::TextArea>(0, 0);
            dudeName->setWidth(340);
            dudeName->setWordWrap(true);
            dudeName->setFont("font1.aaf", {0xa0,0xa0, 0xa0, 0xff});
            dudeName->setText(Game::getInstance()->player()->name()+":");

            auto answer = std::make_unique<UI::TextArea>(0, 0);
            answer->setWidth(316);
            answer->setOffset(26,0);
            answer->setWordWrap(true);
            answer->setFont("font1.aaf", {0x74,0x74, 0x74, 0xff});
            answer->setText(value);

            auto list = getUI<UI::TextAreaList>("list");
            list->addArea(std::move(dudeName));
            list->addArea(std::move(answer));
        }

        void CritterDialogReview::addQuestion(const std::string &value)
        {
            auto crName = std::make_unique<UI::TextArea>(0, 0);
            crName->setWidth(340);
            crName->setWordWrap(true);
            crName->setFont("font1.aaf", {0x3f,0xf8, 0x00, 0xff});
            crName->setText(_critterName+":");

            auto question = std::make_unique<UI::TextArea>(0, 0);
            question->setWidth(316);
            question->setOffset(26,0);
            question->setWordWrap(true);
            question->setFont("font1.aaf", {0x00,0xa4, 0x00, 0xff});
            question->setText(value);

            auto list = getUI<UI::TextAreaList>("list");
            list->addArea(std::move(crName));
            list->addArea(std::move(question));
        }
    }
}
