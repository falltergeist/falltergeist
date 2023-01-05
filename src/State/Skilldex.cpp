// Project includes
#include "../State/Skilldex.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/Location.h"
#include "../State/SettingsMenu.h"
#include "../UI/BigCounter.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        Skilldex::Skilldex(
            std::shared_ptr<UI::IResourceManager> resourceManager
        ) : State(), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void Skilldex::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(false);

            // original coordinates = 455x6
            // background size = 185x368
            auto background = _resourceManager->getImage("art/intrface/skldxbox.frm");
            Graphics::Size rendSize = Game::Game::getInstance()->renderer()->size();
            auto backgroundX = (rendSize.width() + 640 - 2 * background->size().width()) / 2;
            auto backgroundY = (rendSize.height() - 480 + 6);
            background->setPosition({backgroundX, backgroundY});

            // buttons
            auto sneakButton    = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44});
            sneakButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::SNEAK));

            auto lockpickButton = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36});
            lockpickButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::LOCKPICK));

            auto stealButton    = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36 * 2});
            stealButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::STEAL));

            auto trapsButton    = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36 * 3});
            trapsButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::TRAPS));

            auto firstAidButton = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36 * 4});
            firstAidButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::FIRST_AID));

            auto doctorButton   = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36 * 5});
            doctorButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::DOCTOR));

            auto scienceButton  = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36 * 6});
            scienceButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::SCIENCE));

            auto repairButton   = _imageButtonFactory->getByType(ImageButtonType::SKILLDEX_BUTTON, {backgroundX + 14, backgroundY + 44 + 36 * 7});
            repairButton->mouseClickHandler().add(std::bind(&Skilldex::onSkillButtonClick, this, SKILL::REPAIR));

            auto cancelButton   = _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 48, backgroundY + 338});
            cancelButton->mouseClickHandler().add(std::bind(&Skilldex::onCancelButtonClick, this));

            // counters
            auto sneakCounter    = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48), 3);
            sneakCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::SNEAK));

            auto lockpickCounter = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36), 3);
            lockpickCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::LOCKPICK));

            auto stealCounter    = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36 * 2), 3);
            stealCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::STEAL));

            auto trapsCounter    = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36 * 3), 3);
            trapsCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::TRAPS));

            auto firstAidCounter = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36 * 4), 3);
            firstAidCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::FIRST_AID));

            auto doctorCounter   = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36 * 5), 3);
            doctorCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::DOCTOR));

            auto scienceCounter  = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36 * 6), 3);
            scienceCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::SCIENCE));

            auto repairCounter   = std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 111, backgroundY + 48 + 36 * 7), 3);
            repairCounter->setNumber(Game::Game::getInstance()->player()->skillCollection()->skillValue(SKILL::REPAIR));

            // LABELS
            std::string font = "font3.aaf";
            Graphics::Color color = {0xb8, 0x9c, 0x28, 0xff};

            // label: skilldex (100)
            auto skilldexLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 100), backgroundX+56, backgroundY+14);
            skilldexLabel->setFont(font, color);
            skilldexLabel->setWidth(76);
            skilldexLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: sneak (102)
            auto sneakLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 102), backgroundX+17, backgroundY+52);
            sneakLabel->setFont(font, color);
            sneakLabel->setWidth(84);
            sneakLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: lockpick (103)
            auto lockpickLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 103), backgroundX+17, backgroundY+52+36);
            lockpickLabel->setFont(font, color);
            lockpickLabel->setWidth(84);
            lockpickLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: steal (104)
            auto stealLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 104), backgroundX+17, backgroundY+52+36*2);
            stealLabel->setFont(font, color);
            stealLabel->setWidth(84);
            stealLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: traps (105)
            auto trapsLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 105), backgroundX+17, backgroundY+52+36*3);
            trapsLabel->setFont(font, color);
            trapsLabel->setWidth(84);
            trapsLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: first aid (106)
            auto firstAidLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 106), backgroundX+17, backgroundY+52+36*4);
            firstAidLabel->setFont(font, color);
            firstAidLabel->setWidth(84);
            firstAidLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: doctor (107)
            auto doctorLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 107), backgroundX+17, backgroundY+52+36*5);
            doctorLabel->setFont(font, color);
            doctorLabel->setWidth(84);
            doctorLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: science (108)
            auto scienceLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 108), backgroundX+17, backgroundY+52+36*6);
            scienceLabel->setFont(font, color);
            scienceLabel->setWidth(84);
            scienceLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: repair (109)
            auto repairLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 109), backgroundX+17, backgroundY+52+36*7);
            repairLabel->setFont(font, color);
            repairLabel->setWidth(84);
            repairLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

            // label: cancel (101)
            auto cancelButtonLabel = std::make_shared<UI::TextArea>(_t(MSG_SKILLDEX, 101), backgroundX+70, backgroundY+337);
            cancelButtonLabel->setFont(font, color);

            // add all buttons and labels and counters
            addUI(background);
            addUI(sneakButton);
            addUI(lockpickButton);
            addUI(stealButton);
            addUI(trapsButton);
            addUI(firstAidButton);
            addUI(doctorButton);
            addUI(scienceButton);
            addUI(repairButton);
            addUI(cancelButton);
            addUI(skilldexLabel);
            addUI(sneakLabel);
            addUI(lockpickLabel);
            addUI(stealLabel);
            addUI(trapsLabel);
            addUI(firstAidLabel);
            addUI(doctorLabel);
            addUI(scienceLabel);
            addUI(repairLabel);
            addUI(cancelButtonLabel);
            addUI(sneakCounter);
            addUI(lockpickCounter);
            addUI(stealCounter);
            addUI(trapsCounter);
            addUI(firstAidCounter);
            addUI(doctorCounter);
            addUI(scienceCounter);
            addUI(repairCounter);
        }

        void Skilldex::onCancelButtonClick()
        {
            Game::Game::getInstance()->mouse()->popState();
            Game::Game::getInstance()->popState();
        }

        void Skilldex::onKeyDown(Event::Keyboard* event)
        {
            if (event->keyCode() == SDLK_ESCAPE) {
                onCancelButtonClick();
            }
        }

        void Skilldex::onStateActivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void Skilldex::onSkillButtonClick(SKILL skill)
        {
            Game::Game::getInstance()->locationState()->setSkillInUse(skill);
            auto mouse = Game::Game::getInstance()->mouse();
            mouse->popState();
            mouse->setState(Input::Mouse::Cursor::USE);
            Game::Game::getInstance()->popState();
        }
    }
}
