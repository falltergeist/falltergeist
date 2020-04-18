#include "../State/PipBoy.h"
#include "../Event/Keyboard.h"
#include "../Game/Game.h"
#include "../Game/Time.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/MonthCounter.h"
#include "../UI/SmallCounter.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        PipBoy::PipBoy(std::shared_ptr<UI::IResourceManager> resourceManager) : State()
        {
            this->resourceManager = resourceManager;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager);
        }

        PipBoy::~PipBoy()
        {
            Game::getInstance()->mouse()->popState();
        }

        void PipBoy::init()
        {
            if (_initialized) {
                return;
            }

            State::init();

            setModal(true);
            setFullscreen(true);

            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);

            // Background
            auto& background = *addUI(resourceManager->getImage("art/intrface/pip.frm"));
            Point bgPos = Point((Game::getInstance()->renderer()->size() - background.size()) / 2);
            background.setPosition(bgPos);

            // Buttons
            addUI(imageButtonFactory->getByType(ImageButtonType::PIPBOY_ALARM_BUTTON, bgPos.add(124, 13)));
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, bgPos.add(53, 340)));
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, bgPos.add(53, 394)));
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, bgPos.add(53, 432)));
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, bgPos.add(53, 448)))
                ->mouseClickHandler().add(std::bind(&PipBoy::onCloseButtonClick, this, std::placeholders::_1));

            // Date and time

            // Date
            auto gameTime = Game::getInstance()->gameTime();

            {
                auto& day = *makeUI<UI::SmallCounter>(bgPos.add(21, 17));
                day.setLength(2);
                day.setNumber(gameTime->day());
                day.setColor(UI::SmallCounter::Color::WHITE);
                day.setType(UI::SmallCounter::Type::UNSIGNED);
            }

            makeUI<UI::MonthCounter>(
                static_cast<UI::MonthCounter::Month>(gameTime->month()),
            bgPos.add(46, 18));

            {
                auto& year = *makeUI<UI::SmallCounter>(bgPos.add(84, 17));
                year.setLength(4);
                year.setNumber(gameTime->year());
                year.setColor(UI::SmallCounter::Color::WHITE);
                year.setType(UI::SmallCounter::Type::UNSIGNED);
            }

            {
                auto& time = *makeUI<UI::SmallCounter>(bgPos.add(160, 17));
                time.setLength(4);
                time.setNumber((gameTime->hours() * 100) + gameTime->minutes());
                time.setColor(UI::SmallCounter::Color::WHITE);
                time.setType(UI::SmallCounter::Type::UNSIGNED);
            }
        }

        void PipBoy::onCloseButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void PipBoy::onKeyDown(Event::Keyboard* event)
        {
            if (event->keyCode() == SDLK_ESCAPE)
            {
                Game::getInstance()->popState();
            }
        }
    }
}
