#include <memory>
#include <sstream>
#include "../State/NewGame.h"
#include "../Event/State.h"
#include "../functions.h"
#include "../Format/Bio/File.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Helpers/StateLocationHelper.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../State/PlayerCreate.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    using Helpers::StateLocationHelper;
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {

        NewGame::NewGame(std::shared_ptr<UI::IResourceManager> _resourceManager) :
            State{},
            resourceManager{_resourceManager},
            imageButtonFactory{std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager)}
        {
        }

        void NewGame::init()
        {
            if (_initialized) {
                return;
            }

            State::init();

            setFullscreen(true);
            setModal(true);

            auto renderer = Game::getInstance()->renderer();

            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("background", resourceManager->getImage("art/intrface/pickchar.frm"));
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {81, 322}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onBeginGameButtonClick(e);
                });
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {436, 319}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onEditButtonClick(e);
                });
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {81, 424}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onCreateButtonClick(e);
                });
            addUI(imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {461, 424}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onBackButtonClick(e);
                });
            addUI(imageButtonFactory->getByType(ImageButtonType::LEFT_ARROW, {292, 320}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onPrevCharacterButtonClick(e);
                });
            addUI(imageButtonFactory->getByType(ImageButtonType::RIGHT_ARROW, {318, 320}))
                ->mouseClickHandler().add([this](Event::Mouse* e) {
                    this->onNextCharacterButtonClick(e);
                });
            makeNamedUI<UI::ImageList>("images", Point{27, 23}, std::vector<std::shared_ptr<UI::Image>>{
                resourceManager->getImage("art/intrface/combat.frm"),
                resourceManager->getImage("art/intrface/stealth.frm"),
                resourceManager->getImage("art/intrface/diplomat.frm")
            });
            makeNamedUI<UI::TextArea>("name", 300, 40);

            {
                auto& stats1 = *makeNamedUI<UI::TextArea>("stats_1", 0, 70);
                stats1.setWidth(362);
                stats1.setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            }

            makeNamedUI<UI::TextArea>("stats_2", 374, 70);
            makeNamedUI<UI::TextArea>("bio", 437, 40);

            {
                auto& stats3 = *makeNamedUI<UI::TextArea>("stats_3", 294, 150);
                stats3.setWidth(85);
                stats3.setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            }

            makeNamedUI<UI::TextArea>("stats3_values", 383, 150);
        }

        void NewGame::doBeginGame()
        {
            Game::getInstance()->setPlayer(std::move(_characters.at(_selectedCharacter)));
            _characters.clear();

            StateLocationHelper stateLocationHelper;
            Game::getInstance()->setState(stateLocationHelper.getInitialLocationState());
        }

        void NewGame::doEdit()
        {
            Game::getInstance()->setPlayer(std::move(_characters.at(_selectedCharacter)));
            _characters.clear();
            Game::getInstance()->pushState(std::make_unique<PlayerCreate>(resourceManager));
        }

        void NewGame::doCreate()
        {
            auto none = std::make_unique<Game::DudeObject>();
            none->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/blank.gcd"));
            Game::getInstance()->setPlayer(std::move(none));
            Game::getInstance()->pushState(std::make_unique<PlayerCreate>(resourceManager));
        }

        void NewGame::doBack()
        {
            fadeDoneHandler().clear();
            fadeDoneHandler().add([this](Event::Event* event){ this->onBackFadeDone(dynamic_cast<Event::State*>(event)); });
            Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
        }

        void NewGame::doNext()
        {
            if (_selectedCharacter < 2)
            {
                _selectedCharacter++;
            }
            else
            {
                _selectedCharacter = 0;
            }
            _changeCharacter();
        }

        void NewGame::doPrev()
        {
            if (_selectedCharacter > 0)
            {
                _selectedCharacter--;
            }
            else
            {
                _selectedCharacter = 2;
            }
            _changeCharacter();
        }

        void NewGame::onBackButtonClick(Event::Mouse* event)
        {
            doBack();
        }

        void NewGame::onBackFadeDone(Event::State* event)
        {
            fadeDoneHandler().clear();
            Game::getInstance()->popState();
        }

        void NewGame::onPrevCharacterButtonClick(Event::Mouse* event)
        {
            doPrev();
        }

        void NewGame::onNextCharacterButtonClick(Event::Mouse* event)
        {
            doNext();
        }

        void NewGame::_changeCharacter()
        {
            auto& dude = *_characters.at(_selectedCharacter);
            auto& stats1 = *getUI<UI::TextArea>("stats_1");
            stats1 = "";
            stats1
                << _t(MSG_STATS, 100) << " " << (dude.stat(STAT::STRENGTH)     < 10 ? "0" : "") << dude.stat(STAT::STRENGTH)     << "\n"
                << _t(MSG_STATS, 101) << " " << (dude.stat(STAT::PERCEPTION)   < 10 ? "0" : "") << dude.stat(STAT::PERCEPTION)   << "\n"
                << _t(MSG_STATS, 102) << " " << (dude.stat(STAT::ENDURANCE)    < 10 ? "0" : "") << dude.stat(STAT::ENDURANCE)    << "\n"
                << _t(MSG_STATS, 103) << " " << (dude.stat(STAT::CHARISMA)     < 10 ? "0" : "") << dude.stat(STAT::CHARISMA)     << "\n"
                << _t(MSG_STATS, 104) << " " << (dude.stat(STAT::INTELLIGENCE) < 10 ? "0" : "") << dude.stat(STAT::INTELLIGENCE) << "\n"
                << _t(MSG_STATS, 105) << " " << (dude.stat(STAT::AGILITY)      < 10 ? "0" : "") << dude.stat(STAT::AGILITY)      << "\n"
                << _t(MSG_STATS, 106) << " " << (dude.stat(STAT::LUCK)         < 10 ? "0" : "") << dude.stat(STAT::LUCK)         << "\n";

            auto& stats2 = *getUI<UI::TextArea>("stats_2");
            stats2 = "";
            stats2
                << _t(MSG_STATS, dude.stat(STAT::STRENGTH)     + 300) << "\n"
                << _t(MSG_STATS, dude.stat(STAT::PERCEPTION)   + 300) << "\n"
                << _t(MSG_STATS, dude.stat(STAT::ENDURANCE)    + 300) << "\n"
                << _t(MSG_STATS, dude.stat(STAT::CHARISMA)     + 300) << "\n"
                << _t(MSG_STATS, dude.stat(STAT::INTELLIGENCE) + 300) << "\n"
                << _t(MSG_STATS, dude.stat(STAT::AGILITY)      + 300) << "\n"
                << _t(MSG_STATS, dude.stat(STAT::LUCK)         + 300) << "\n";

            getUI<UI::TextArea>("bio")->setText(dude.biography());
            getUI<UI::TextArea>("name")->setText(dude.name());
            getUI<UI::ImageList>("images")->setCurrentImage(_selectedCharacter);

            std::stringstream stats3;
            stats3 << _t(MSG_MISC,  16)  << "\n"  // Hit Points
                   << _t(MSG_STATS, 109) << "\n"  // Armor Class
                   << _t(MSG_MISC,  15)  << "\n"  // Action Points
                   << _t(MSG_STATS, 111) << "\n"; // Melee Damage

            std::stringstream stats3_values;
            stats3_values << dude.hitPoints() << "/" << dude.hitPointsMax() << "\n"
                          << dude.armorClass() << "\n"
                          << dude.actionPoints() << "\n"
                          << dude.meleeDamage() << "\n";

            for (auto i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
            {
                if (dude.skillTagged((SKILL)i))
                {
                    stats3 << "\n" << _t(MSG_SKILLS, 100 + i);
                    stats3_values << "\n" << dude.skillValue((SKILL)i) << "%";
                }
            }

            for (auto i = (unsigned)TRAIT::FAST_METABOLISM; i <= (unsigned)TRAIT::GIFTED; i++)
            {
                if (dude.traitTagged((TRAIT)i))
                {
                    stats3 << "\n" << _t(MSG_TRAITS, 100 + i);
                }
            }

            getUI<UI::TextArea>("stats_3")->setText(stats3.str());
            getUI<UI::TextArea>("stats3_values")->setText(stats3_values.str());
        }

        void NewGame::onEditButtonClick(Event::Mouse* event)
        {
            doEdit();
        }

        void NewGame::onCreateButtonClick(Event::Mouse* event)
        {
            doCreate();
        }

        void NewGame::onBeginGameButtonClick(Event::Mouse* event)
        {
            doBeginGame();
        }

        void NewGame::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_b:
                    doBack();
                    break;
                case SDLK_t:
                    doBeginGame();
                    break;
                case SDLK_c:
                    doCreate();
                    break;
                case SDLK_m:
                    doEdit();
                    break;
                case SDLK_LEFT:
                    doPrev();
                    break;
                case SDLK_RIGHT:
                    doNext();
                    break;
            }
        }

        void NewGame::onStateActivate(Event::State* event)
        {
            {
                auto combat = std::make_unique<Game::DudeObject>();
                combat->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
                combat->setBiography(ResourceManager::getInstance()->bioFileType("premade/combat.bio")->text());
                _characters.emplace_back(std::move(combat));
            }

            {
                auto stealth = std::make_unique<Game::DudeObject>();
                stealth->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/stealth.gcd"));
                stealth->setBiography(ResourceManager::getInstance()->bioFileType("premade/stealth.bio")->text());
                _characters.emplace_back(std::move(stealth));
            }

            {
                auto diplomat = std::make_unique<Game::DudeObject>();
                diplomat->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/diplomat.gcd"));
                diplomat->setBiography(ResourceManager::getInstance()->bioFileType("premade/diplomat.bio")->text());
                _characters.emplace_back(std::move(diplomat));
            }

            _changeCharacter();

            Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
        }
    }
}
