#include "../functions.h"
#include "../State/PipBoy.h"
#include "../Event/Keyboard.h"
#include "../Game/Game.h"
#include "../Game/Time.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../UI/Base.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/MonthCounter.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        PipBoy::PipBoy(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        PipBoy::~PipBoy()
        {
            Game::Game::getInstance()->mouse()->popState();
        }

        void PipBoy::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);

            // Background
            auto background = resourceManager->getImage("art/intrface/pip.frm");
            Point backgroundPos = Point((Game::Game::getInstance()->renderer()->size() - background->size()) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();
            background->setPosition(backgroundPos);

            // Pipboy logo
            auto logo = resourceManager->getImage("art/intrface/pipx.frm");
            logo->setPosition({ backgroundX + 325, backgroundY + 165 });

            // Buttons
            auto alarmButton = imageButtonFactory->getByType(ImageButtonType::PIPBOY_ALARM_BUTTON, {backgroundX + 124, backgroundY + 13});
            auto statusButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 53, backgroundY + 340});
            auto automapsButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 53, backgroundY + 394});
            auto archivesButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 53, backgroundY + 423});
            auto closeButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 53, backgroundY + 448});
            closeButton->mouseClickHandler().add(std::bind(&PipBoy::onCloseButtonClick, this, std::placeholders::_1));
            // Date and time

            // Date
            auto gameTime = Game::Game::getInstance()->gameTime();

            auto day = new UI::SmallCounter(backgroundPos + Point(21, 17));
            day->setLength(2);
            day->setNumber(gameTime->day());
            day->setColor(UI::SmallCounter::Color::WHITE);
            day->setType(UI::SmallCounter::Type::UNSIGNED);

            auto month = new UI::MonthCounter(
                static_cast<UI::MonthCounter::Month>(gameTime->month()),
                backgroundPos + Point(46, 18)
            );

            auto year = new UI::SmallCounter(backgroundPos + Point(84, 17));
            year->setLength(4);
            year->setNumber(gameTime->year());
            year->setColor(UI::SmallCounter::Color::WHITE);
            year->setType(UI::SmallCounter::Type::UNSIGNED);

            // Time
            auto time = new UI::SmallCounter(backgroundPos + Point(160, 17));
            time->setLength(4);
            time->setNumber((gameTime->hours() * 100) + gameTime->minutes());
            time->setColor(UI::SmallCounter::Color::WHITE);
            time->setType(UI::SmallCounter::Type::UNSIGNED);

            addUI(background);
            addUI(logo);

            addUI(alarmButton);
            addUI(statusButton);
            addUI(automapsButton);
            addUI(archivesButton);

            addUI(day);
            addUI(month);
            addUI(year);
            addUI(time);

            addUI(closeButton);

            // Special date greeting
            std::string greeting = getSpecialGreeting(gameTime->month(), gameTime->day());
            if (!greeting.empty()) {
                addUI(new UI::TextArea(greeting, backgroundX+385, backgroundY+325));
            }
        }

        void PipBoy::onCloseButtonClick(Event::Mouse* event)
        {
            Game::Game::getInstance()->popState();
        }

        void PipBoy::onKeyDown(Event::Keyboard* event)
        {
            if (event->keyCode() == SDLK_ESCAPE)
            {
                Game::Game::getInstance()->popState();
            }
        }

        std::string PipBoy::getSpecialGreeting(int month, int day) {

            if (month == 1 && day == 1) {
                return _t(MSG_PIPBOY, 100); // New Year
            }
            if (month == 2 && day == 14) {
                return _t(MSG_PIPBOY, 101); // Valentine's Day
            }
            if (month == 4 && day == 1) {
                return _t(MSG_PIPBOY, 102); // April fools
            }
            if (month == 10 && day == 6) {
                return _t(MSG_PIPBOY, 103); // Fallout shipping day
            }
            if (month == 7 && day == 4) {
                return _t(MSG_PIPBOY, 104); // Independence day
            }
            if (month == 10 && day == 31) {
                return _t(MSG_PIPBOY, 105); // Halloween
            }
            if (month == 11 && day == 26) {
                return _t(MSG_PIPBOY, 106); // Thanksgiving
            }
            if (month == 12 && day == 24) {
                return _t(MSG_PIPBOY, 107); // Christmas
            }

            return std::string();
        }
    }
}
