// Project includes
#include "../State/NewGame.h"
#include "../Event/State.h"
#include "../functions.h"
#include "../Format/Bio/File.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/TraitCollection.h"
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

// Third-party includes

// stdlib
#include <memory>
#include <sstream>

namespace Falltergeist
{
    namespace State
    {
        using Helpers::StateLocationHelper;
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;
        using TextArea = Falltergeist::UI::TextArea;

        NewGame::NewGame(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<ILogger> logger
        ) : State(), _logger(logger), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void NewGame::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(true);
            setModal(true);

            auto renderer = Game::Game::getInstance()->renderer();

            setPosition((renderer->size() - Point(640, 480)) / 2);

            addUI("background", _resourceManager->getImage("art/intrface/pickchar.frm"));

            auto beginGameButton = addUI(_imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {81, 322}));
            beginGameButton->mouseClickHandler().add(std::bind(&NewGame::onBeginGameButtonClick, this, std::placeholders::_1));

            auto editButton = addUI(_imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {436, 319}));
            editButton->mouseClickHandler().add(std::bind(&NewGame::onEditButtonClick, this, std::placeholders::_1));

            auto createButton = addUI(_imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {81, 424}));
            createButton->mouseClickHandler().add(std::bind(&NewGame::onCreateButtonClick, this, std::placeholders::_1));

            auto backButton = addUI(_imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {461, 424}));
            backButton->mouseClickHandler().add(std::bind(&NewGame::onBackButtonClick, this, std::placeholders::_1));

            auto prevCharacterButton = addUI(_imageButtonFactory->getByType(ImageButtonType::LEFT_ARROW, {292, 320}));
            prevCharacterButton->mouseClickHandler().add(std::bind(&NewGame::onPrevCharacterButtonClick, this, std::placeholders::_1));

            auto nextCharacterButton = addUI(_imageButtonFactory->getByType(ImageButtonType::RIGHT_ARROW, {318, 320}));
            nextCharacterButton->mouseClickHandler().add(std::bind(&NewGame::onNextCharacterButtonClick, this, std::placeholders::_1));

            std::vector<std::shared_ptr<UI::Image>> images = {
                _resourceManager->getImage("art/intrface/combat.frm"),
                _resourceManager->getImage("art/intrface/stealth.frm"),
                _resourceManager->getImage("art/intrface/diplomat.frm")
            };
            addUI("images", std::make_shared<UI::ImageList>(Graphics::Point(27, 23), images));

            addUI("name", std::make_shared<UI::TextArea>(300, 40));

            addUI("stats_1", std::make_shared<UI::TextArea>(0, 70));
            getUI<TextArea>("stats_1")->setWidth(362);
            getUI<TextArea>("stats_1")->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

            addUI("stats_2", std::make_shared<UI::TextArea>(374, 70));
            addUI("bio",     std::make_shared<UI::TextArea>(437, 40));

            addUI("stats_3", std::make_shared<UI::TextArea>(294, 150));
            getUI<TextArea>("stats_3")->setWidth(85);
            getUI<TextArea>("stats_3")->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

            addUI("stats3_values", std::make_shared<UI::TextArea>(383, 150));
        }

        void NewGame::doBeginGame()
        {
            Game::Game::getInstance()->setPlayer(std::move(_characters.at(_selectedCharacter)));
            _characters.clear();

            StateLocationHelper stateLocationHelper(_logger);
            Game::Game::getInstance()->setState(stateLocationHelper.getInitialLocationState());
        }

        void NewGame::doEdit()
        {
            Game::Game::getInstance()->setPlayer(std::move(_characters.at(_selectedCharacter)));
            _characters.clear();
            Game::Game::getInstance()->pushState(new PlayerCreate(_resourceManager, _logger));
        }

        void NewGame::doCreate()
        {
            auto blankTraitCollection = std::make_shared<Game::TraitCollection>();
            auto none = std::make_unique<Game::DudeObject>(blankTraitCollection);
            none->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/blank.gcd"));
            Game::Game::getInstance()->setPlayer(std::move(none));
            Game::Game::getInstance()->pushState(new PlayerCreate(_resourceManager, _logger));
        }

        void NewGame::doBack()
        {
            fadeDoneHandler().clear();
            fadeDoneHandler().add([this](Event::Event* event){ this->onBackFadeDone(dynamic_cast<Event::State*>(event)); });
            Game::Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
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
            Game::Game::getInstance()->popState();
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
            auto& dude = _characters.at(_selectedCharacter);
           *getUI<TextArea>("stats_1") = "";
           *getUI<TextArea>("stats_1")
                << _t(MSG_STATS, 100) << " " << (dude->stat(STAT::STRENGTH)     < 10 ? "0" : "") << dude->stat(STAT::STRENGTH)     << "\n"
                << _t(MSG_STATS, 101) << " " << (dude->stat(STAT::PERCEPTION)   < 10 ? "0" : "") << dude->stat(STAT::PERCEPTION)   << "\n"
                << _t(MSG_STATS, 102) << " " << (dude->stat(STAT::ENDURANCE)    < 10 ? "0" : "") << dude->stat(STAT::ENDURANCE)    << "\n"
                << _t(MSG_STATS, 103) << " " << (dude->stat(STAT::CHARISMA)     < 10 ? "0" : "") << dude->stat(STAT::CHARISMA)     << "\n"
                << _t(MSG_STATS, 104) << " " << (dude->stat(STAT::INTELLIGENCE) < 10 ? "0" : "") << dude->stat(STAT::INTELLIGENCE) << "\n"
                << _t(MSG_STATS, 105) << " " << (dude->stat(STAT::AGILITY)      < 10 ? "0" : "") << dude->stat(STAT::AGILITY)      << "\n"
                << _t(MSG_STATS, 106) << " " << (dude->stat(STAT::LUCK)         < 10 ? "0" : "") << dude->stat(STAT::LUCK)         << "\n";

            *getUI<TextArea>("stats_2") = "";
            *getUI<TextArea>("stats_2")
                << _t(MSG_STATS, dude->stat(STAT::STRENGTH)     + 300) << "\n"
                << _t(MSG_STATS, dude->stat(STAT::PERCEPTION)   + 300) << "\n"
                << _t(MSG_STATS, dude->stat(STAT::ENDURANCE)    + 300) << "\n"
                << _t(MSG_STATS, dude->stat(STAT::CHARISMA)     + 300) << "\n"
                << _t(MSG_STATS, dude->stat(STAT::INTELLIGENCE) + 300) << "\n"
                << _t(MSG_STATS, dude->stat(STAT::AGILITY)      + 300) << "\n"
                << _t(MSG_STATS, dude->stat(STAT::LUCK)         + 300) << "\n";

            getUI<TextArea>("bio")->setText(dude->biography());
            getUI<TextArea>("name")->setText(dude->name());
            getUI<UI::ImageList>("images")->setCurrentImage(_selectedCharacter);

            std::string stats3  = _t(MSG_MISC,  16)  + "\n"    // Hit Points
                                + _t(MSG_STATS, 109) + "\n"     // Armor Class
                                + _t(MSG_MISC,  15)  + "\n"     // Action Points
                                + _t(MSG_STATS, 111) + "\n";    // Melee Damage

            std::string stats3_values   = std::to_string(dude->hitPointsMax()) + "/" + std::to_string(dude->hitPointsMax()) + "\n"
                                        + std::to_string(dude->armorClass())   + "\n"
                                        + std::to_string(dude->actionPoints()) + "\n"
                                        + std::to_string(dude->meleeDamage())  + "\n";

            for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
            {
                if (dude->skillTagged((SKILL)i))
                {
                    stats3 += "\n" + _t(MSG_SKILLS, 100 + i);
                    stats3_values += "\n" + std::to_string(dude->skillValue((SKILL)i)) + "%";
                }
            }
            for (unsigned i = (unsigned)TRAIT::FAST_METABOLISM; i <= (unsigned)TRAIT::GIFTED; i++)
            {
                if (dude->traitCollection()->hasTrait((TRAIT)i))
                {
                    stats3 += "\n" + _t(MSG_TRAITS, 100 + i);
                }
            }
            getUI<TextArea>("stats_3")->setText(stats3);
            getUI<TextArea>("stats3_values")->setText(stats3_values);
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
            auto combatTraitCollection = std::make_shared<Game::TraitCollection>();
            auto combat = std::make_unique<Game::DudeObject>(combatTraitCollection);
            combat->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
            combat->setBiography(ResourceManager::getInstance()->bioFileType("premade/combat.bio")->text());
            _characters.emplace_back(std::move(combat));

            auto stealthTraitCollection = std::make_shared<Game::TraitCollection>();
            auto stealth = std::make_unique<Game::DudeObject>(stealthTraitCollection);
            stealth->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/stealth.gcd"));
            stealth->setBiography(ResourceManager::getInstance()->bioFileType("premade/stealth.bio")->text());
            _characters.emplace_back(std::move(stealth));

            auto diplomatTraitCollection = std::make_shared<Game::TraitCollection>();
            auto diplomat = std::make_unique<Game::DudeObject>(diplomatTraitCollection);
            diplomat->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/diplomat.gcd"));
            diplomat->setBiography(ResourceManager::getInstance()->bioFileType("premade/diplomat.bio")->text());
            _characters.emplace_back(std::move(diplomat));

            _changeCharacter();

            Game::Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
        }
    }
}
