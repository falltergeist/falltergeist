// Project includes
#include "../State/PlayerEdit.h"
#include "../Font.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../State/PlayerEditAlert.h"
#include "../UI/BigCounter.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/HiddenMask.h"
#include "../UI/Image.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"
#include "../UI/TextAreaList.h"
#include "../UI/Rectangle.h"

// Third-party includes

// stdlib
#include <sstream>

namespace Falltergeist
{
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        PlayerEdit::PlayerEdit(std::shared_ptr<UI::IResourceManager> resourceManager)
            : State(), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void PlayerEdit::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            auto player = Game::Game::getInstance()->player();

            // background
            auto background = _resourceManager->getImage("art/intrface/edtredt.frm");
            Point backgroundPos = Point((Game::Game::getInstance()->renderer()->size() - background->size()) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();
            background->setPosition(backgroundPos);
            addUI("bg",background);

            // STATS
            std::string imagesStats[] = { "strength", "perceptn", "endur", "charisma", "intel", "agility", "luck"};
            for (unsigned int i = 0; i != 7; ++i)
            {
                std::stringstream ss;
                ss << "stats_" << (i+1);

                _addTitle(ss.str(), _t(MSG_STATS, 100 + i));       // stat title
                _addDescription(ss.str(), _t(MSG_STATS, 200 + i)); // stat description
                _addImage(ss.str(), _resourceManager->getImage("art/skilldex/" + imagesStats[i] + ".frm")); // stat image
                _addLabel(ss.str(), std::make_shared<UI::TextArea>(backgroundX+104, backgroundY+46+33*i));          // stat value label
                _addCounter(ss.str(), std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 59, static_cast<int>(backgroundY + 37 + 33 * i))));       // stat value counter
                _addMask(ss.str(), std::make_shared<UI::HiddenMask>(133, 29, backgroundX+14, backgroundY+36+33*i)); // stat click mask
            }

            // LEVEL window
            auto level = player->level();
            int expNext = level*(level+1)*500; // experience needed for next level
            std::string imagesLevel[] = { "level", "exper", "levelnxt"};
            for (unsigned int i = 0; i != 3; ++i)
            {
                std::stringstream ss;
                std::stringstream tmp;
                std::string line = "";
                ss << "level_" << (i+1);
                // Level 401 stat, Experience 402 stat, Next level 122 editor
                switch (i)
                {
                    case 0:
                        line = _t(MSG_STATS, 401);
                        break;
                    case 1:
                        line = _t(MSG_STATS, 402);
                        break;
                    case 2:
                        line = _t(MSG_EDITOR, 122);
                        break;
                }
                _addTitle(ss.str(), line);
                // description: level: 501 stat, exp: 502 stat, levelnxt: editor 123
                switch (i)
                {
                    case 0:
                        line = _t(MSG_STATS, 501);
                        break;
                    case 1:
                        line = _t(MSG_STATS, 502);
                        break;
                    case 2:
                        line = _t(MSG_EDITOR, 123);
                        break;
                }
                _addDescription(ss.str(), line); // level description
                _addImage(ss.str(), _resourceManager->getImage("art/skilldex/" + imagesLevel[i] + ".frm")); // stat image
                tmp.str() = "";
                tmp << _t(MSG_EDITOR, 113 + i) << " ";
                switch (i)
                {
                    case 0:
                        tmp << player->level();
                        break;
                    case 1:
                        tmp << player->experience();
                        break;
                    case 2:
                        tmp << expNext;
                        break;
                }
                _addLabel(ss.str(), std::make_shared<UI::TextArea>(tmp.str(), backgroundX + 32, backgroundY + 280 + 11*i));            // stat value label
            }

            // SKILLS
            std::string imagesSkills[]  = { "gunsml", "gunbig", "energywp", "unarmed", "melee", "throwing", "firstaid", "doctor", "sneak",
                                            "lockpick", "steal", "traps", "science", "repair", "speech", "barter", "gambling", "outdoors"};
            for (unsigned int i = 0; i != 18; ++i)
            {
                std::stringstream ss;
                ss << "skills_" << (i+1);
                _addTitle(ss.str(), _t(MSG_SKILLS, 100 + i));
                _addDescription(ss.str(), _t(MSG_SKILLS, 200 + i));
                _addImage(ss.str(),  _resourceManager->getImage("art/skilldex/" + imagesSkills[i] + ".frm"));
                _addLabel(ss.str(),  std::make_shared<UI::TextArea>(_t(MSG_SKILLS, 100 + i), backgroundX+377, backgroundY+27+11*i))->setWidth(240);
                _addLabel(ss.str() + "_value",  std::make_shared<UI::TextArea>("", backgroundX+577, backgroundY+27+11*i));
            }
            // Free skill points counts
            _addCounter("skillsPoints", std::make_shared<UI::BigCounter>(Graphics::Point(backgroundX + 522, backgroundY + 228)));

            // HEALTH CONDITION
            std::string imagesHealth[] = { "hitpoint", "poisoned", "radiated", "eyedamag", "armright", "armleft", "legright", "legleft"};
            _addTitle("health_1", _t(MSG_EDITOR, 300));
            _addLabel("health_1", std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 300), backgroundX+194, backgroundY+46)); //health
            _addDescription("health_1", _t(MSG_STATS, 207));
            _addImage("health_1", _resourceManager->getImage("art/skilldex/" + imagesHealth[0] + ".frm"));

            for (unsigned int i = 0; i != 7; ++i)
            {
                std::stringstream ss;
                ss << "health_" << (i+2);
                _addTitle(ss.str(), _t(MSG_EDITOR, 312 + i));
                _addDescription(ss.str(), _t(MSG_EDITOR, 400 + i));
                _addLabel(ss.str(), std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 312+i), backgroundX+194, backgroundY+46+13*(i+1)))->setFont("font1.aaf", {0x18, 0x30, 0x18, 0xff});
                _addImage(ss.str(), _resourceManager->getImage("art/skilldex/" + imagesHealth[i+1] + ".frm"));
            }

            // PLAYER PARAMS
            std::string imagesParams[] = {"armorcls", "actionpt", "carryamt", "meleedam", "damresis", "poisnres", "radresis", "sequence", "healrate", "critchnc"};
            unsigned int labels[] = {302, 301, 311, 304, 305, 306, 307, 308, 309, 310};
            const int params[] = {109, 108, 112, 111, 124, 132, 131, 113, 114, 115};
            for (unsigned int i = 0; i != 10; ++i)
            {
                std::stringstream ss;
                ss << "params_" << (i+1);
                _addTitle(ss.str(), _t(MSG_STATS, params[i]));
                _addDescription(ss.str(), _t(MSG_STATS, params[i] + 100));
                _addImage(ss.str(), _resourceManager->getImage("art/skilldex/" + imagesParams[i] + ".frm"));
                _addLabel(ss.str(), std::make_shared<UI::TextArea>(_t(MSG_EDITOR, labels[i]), backgroundX + 194, backgroundY + 179 + 13*i));
                _addLabel(ss.str() + "_value",  std::make_shared<UI::TextArea>("", backgroundX + 288, backgroundY + 179 + 13*i));
            }

            _addButton("print", _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 345, backgroundY + 454}));
            _addButton("done",  _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 455, backgroundY + 454}));
            _addButton("cancel",_imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 554, backgroundY + 454}));

            auto font3_b89c28ff = ResourceManager::getInstance()->font("font3.aaf");
            Graphics::Color color = {0xb8, 0x9c, 0x28, 0xff};

            _addLabel("print", std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 103), backgroundX+365, backgroundY+453))->setFont(font3_b89c28ff, color);
            _addLabel("next",  std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 100), backgroundX+473, backgroundY+453))->setFont(font3_b89c28ff, color);
            _addLabel("cancel",std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 102), backgroundX+571, backgroundY+453))->setFont(font3_b89c28ff, color);
            auto nameLbl = _addLabel("name", std::make_shared<UI::TextArea>(Game::Game::getInstance()->player()->name(), backgroundX+17, backgroundY+7));
            nameLbl->setWidth(150);
            nameLbl->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            nameLbl->setFont(font3_b89c28ff, color);
            _addLabel("age",     std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 104), backgroundX+163, backgroundY+7))->setFont(font3_b89c28ff, color);
            _addLabel("gender",  std::make_shared<UI::TextArea>(_t(MSG_EDITOR, Game::Game::getInstance()->player()->gender() == GENDER::MALE ? 107 : 108), backgroundX+250, backgroundY+7))->setFont(font3_b89c28ff, color);

            _addLabel("label_1", std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 112), backgroundX+398, backgroundY+233))->setFont(font3_b89c28ff, color); // skill points on tag skills place!
            _addLabel("label_3", std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 117), backgroundX+383, backgroundY+5))->setFont(font3_b89c28ff, color);  // skills

            _addTitle("label_1", _t(MSG_EDITOR, 112));
            _addTitle("label_2", _t(MSG_EDITOR, 146));
            _addTitle("label_3", _t(MSG_EDITOR, 150));
            _addTitle("label_4", _t(MSG_EDITOR, 144));
            _addDescription("label_1", _t(MSG_EDITOR, 131));
            _addDescription("label_2", _t(MSG_EDITOR, 147));
            _addDescription("label_3", _t(MSG_EDITOR, 151));
            _addDescription("label_4", _t(MSG_EDITOR, 145));
            _addImage("label_1", _resourceManager->getImage("art/skilldex/skills.frm"));
            _addImage("label_2", _resourceManager->getImage("art/skilldex/traits.frm"));
            _addImage("label_3", _resourceManager->getImage("art/skilldex/skills.frm"));
            _addImage("label_4", _resourceManager->getImage("art/skilldex/skills.frm"));

            // Name label -- ex Name change button
            //_addButton("name",  std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PLAYER_NAME, backgroundX+13, backgroundY+0)));
            auto nameLabel = _resourceManager->getImage("art/intrface/nameoff.frm");
            nameLabel->setPosition(backgroundPos + Point(13, 0));
            addUI(nameLabel);

            // Age label -- ex Age change button
            //_addButton("age",  std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PLAYER_AGE, backgroundX+156, backgroundY+0)));
            auto ageLabel = _resourceManager->getImage("art/intrface/ageoff.frm");
            ageLabel->setPosition(backgroundPos + Point(156, 0));
            addUI(ageLabel);

            // Gender label -- ex Gender change button
            //_addButton("gender",  std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PLAYER_GENDER, backgroundX+236, backgroundY+0)));
            auto genderLabel = _resourceManager->getImage("art/intrface/sexoff.frm");
            genderLabel->setPosition(backgroundPos + Point(236, 0));
            addUI(genderLabel);

            // add buttons to the state
            for (auto& button : _buttons) {
                button.second->mouseClickHandler().add([=](Event::Mouse*) {
                    _onButtonClick(button.second);
                });
                addUI(button.second);
            }

            // add labels to the state
            // reverse iterator to change drawing order
            for(auto it = _labels.rbegin(); it != _labels.rend(); ++it)
            {
                auto label = it->second;
                label->mouseDownHandler().add([=](Event::Mouse*) { onLabelClick(label); });
                addUI(label);
            }

            // add counters to the state
            for(auto it = _counters.begin(); it != _counters.end(); ++it)
            {
                addUI(it->second);
            }

            // add hidden masks
            for(auto it = _masks.begin(); it != _masks.end(); ++it)
            {
                auto mask = it->second;
                mask->mouseDownHandler().add([=](Event::Mouse*) { onMaskClick(mask); });
                addUI(mask);
            }

            _selectedImage = _images.at("stats_1");
            _selectedLabel = _labels.at("stats_1");
            _selectedImage->setPosition(backgroundPos + Point(480, 310));

            _title = std::make_shared<UI::TextArea>("", backgroundX+350, backgroundY+275);
            _title->setFont("font2.aaf", {0,0,0,0xff});
            addUI(_title);

            auto line = std::make_shared<UI::Rectangle>(backgroundPos + Point(350, 300), Graphics::Size(270, 2), Graphics::Color(0x00, 0x00, 0x00, 0xff));
            addUI(line);

            _description = std::make_shared<UI::TextArea>("", backgroundX+350, backgroundY+315);
            _description->setFont("font1.aaf", {0,0,0,0xff});
            _description->setSize({140, 120});
            _description->setWordWrap(true);

            // TABS
            auto tabs = std::make_shared<UI::ImageList>(Graphics::Point(backgroundX + 10, backgroundY + 325), std::vector<std::shared_ptr<UI::Image>>({
                _resourceManager->getImage("art/intrface/perksfdr.frm"),
                _resourceManager->getImage("art/intrface/karmafdr.frm"),
                _resourceManager->getImage("art/intrface/killsfdr.frm")
            }));
            tabs->mouseClickHandler().add(std::bind(&PlayerEdit::onTabClick, this, std::placeholders::_1));
            addUI("tabs", tabs);

            // Tab labels: perks, karma, kills
            for (unsigned int i = 0; i < 3; i++) {
                auto tab = addUI("tab_" + std::to_string(i),
                                     std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 109+i), backgroundX+10+35+(100*i), backgroundY+325+7+(i == 0 ? -1 : 1)));
                std::dynamic_pointer_cast<UI::TextArea>(tab)->setFont(font3_b89c28ff, color);
            }

            Point tabContentPos = tabs->position() + Point(25, 45);

            // Perks and traits
            auto perksAndTraits = std::make_shared<UI::TextAreaList>(tabContentPos);
            perksAndTraits->setSize({ 0, 100 });

            auto traits = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 156), Graphics::Point(0, 0));
            traits->setWidth(270);
            traits->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            perksAndTraits->addArea(traits);

            for (unsigned i = static_cast<unsigned>(TRAIT::FAST_METABOLISM); i <= static_cast<unsigned>(TRAIT::GIFTED); i++)
            {
                if (player->traitTagged(static_cast<TRAIT>(i)))
                {
                    perksAndTraits->addArea(std::make_shared<UI::TextArea>(_t(MSG_TRAITS, 100 + i), Graphics::Point(0, 0)));
                }
            }

            auto perks = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 109), Graphics::Point(0, 0));
            perks->setWidth(270);
            perks->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            perksAndTraits->addArea(perks);

            addUI("tab_perks", perksAndTraits);

            // Karma overview
            auto karma = std::make_shared<UI::TextAreaList>(tabContentPos);
            karma->setSize({ 0, 100 });
            karma->setVisible(false);

            karma->addArea(std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 125), Graphics::Point(0, 0)));

            auto reputation = std::make_shared<UI::TextArea>(_t(MSG_EDITOR, 4000), Graphics::Point(0, 0));
            reputation->setWidth(270);
            reputation->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            karma->addArea(reputation);

            addUI("tab_karma", karma);

            // Killing statistics
            auto killEnemyNames = std::make_shared<UI::TextAreaList>(tabContentPos);
            auto killEnemyScore = std::make_shared<UI::TextAreaList>(tabContentPos + Point(270, 0));
            killEnemyNames->setSize({ 0, 100 });
            killEnemyScore->setSize({ 0, 100 });
            killEnemyNames->setVisible(false);
            killEnemyScore->setVisible(false);

            // TODO: _underline_. Just for testing. Real kill stats should be stored in a map inside DudeObject(?)
            for (unsigned int i = 0; i < 19; i++) {
                killEnemyNames->addArea(std::make_shared<UI::TextArea>(_t(MSG_PROTO, 1450+i), Graphics::Point(0, 0)));
                killEnemyScore->addArea(std::make_shared<UI::TextArea>(std::to_string(i), Graphics::Point(0, 0)));
            }

            addUI("tab_kills_enemies", killEnemyNames);
            addUI("tab_kills_score", killEnemyScore);

            auto tabsArrowUp = _imageButtonFactory->getByType(ImageButtonType::SMALL_UP_ARROW, {backgroundX + 317, backgroundY + 363});
            tabsArrowUp->mouseClickHandler().add([=](...) {
                switch (tabs->currentImage()) {
                case 0: perksAndTraits->scrollUp();
                    break;
                case 1: karma->scrollUp();
                    break;
                case 2: killEnemyNames->scrollUp(); killEnemyScore->scrollUp();
                    break;
                }
            });
            addUI(tabsArrowUp);

            auto tabsArrowDown = _imageButtonFactory->getByType(ImageButtonType::SMALL_DOWN_ARROW, {backgroundX + 317, backgroundY + 376});
            tabsArrowDown->mouseClickHandler().add([=](...) {
                switch (tabs->currentImage()) {
                case 0: perksAndTraits->scrollDown();
                    break;
                case 1: karma->scrollDown();
                    break;
                case 2: killEnemyNames->scrollDown(); killEnemyScore->scrollDown();
                    break;
                }
            });
            addUI(tabsArrowDown);
        }

        std::shared_ptr<UI::TextArea> PlayerEdit::_addLabel(const std::string& name, std::shared_ptr<UI::TextArea> label)
        {
            _labels.insert(std::pair<std::string, std::shared_ptr<UI::TextArea>>(name, label));
            return label;
        }

        std::shared_ptr<UI::ImageButton> PlayerEdit::_addButton(const std::string& name, std::shared_ptr<UI::ImageButton> button)
        {
            _buttons.insert(std::pair<std::string, std::shared_ptr<UI::ImageButton>>(name, button));
            return button;
        }

        std::shared_ptr<UI::BigCounter> PlayerEdit::_addCounter(const std::string& name, std::shared_ptr<UI::BigCounter> counter)
        {
            _counters.insert(std::pair<std::string, std::shared_ptr<UI::BigCounter>>(name, counter));
            return counter;
        }

        std::shared_ptr<UI::HiddenMask> PlayerEdit::_addMask(const std::string& name, std::shared_ptr<UI::HiddenMask> mask)
        {
            _masks.insert(std::pair<std::string, std::shared_ptr<UI::HiddenMask>>(name, mask));
            return mask;
        }

        void PlayerEdit::_addTitle(const std::string& name, std::string title)
        {
            _titles.insert(std::pair<std::string,std::string>(name, title));
        }

        void PlayerEdit::_addDescription(const std::string& name, std::string description)
        {
            _descriptions.insert(std::pair<std::string,std::string>(name, description));
        }

        void PlayerEdit::_addImage(const std::string& name, std::shared_ptr<UI::Image> image)
        {
            _images.insert(std::pair<std::string, std::shared_ptr<UI::Image>>(name, image));
        }

        void PlayerEdit::think(const float &deltaTime)
        {
            State::think(deltaTime);
            auto player = Game::Game::getInstance()->player();

            *_labels.at("name") = player->name();
            *_labels.at("age") = _t(MSG_EDITOR, 104) + " " + std::to_string(player->age());
            *_labels.at("gender") = _t(MSG_EDITOR, player->gender() == GENDER::MALE ? 107 : 108);

            _counters.at("skillsPoints")->setNumber(player->skillsPoints());

            *_labels.at("health_1") = _t(MSG_EDITOR, 300) + "  " + std::to_string(player->hitPointsMax()) + "/" + std::to_string(player->hitPointsMax());
            *_labels.at("params_1_value") = player->armorClass();
            *_labels.at("params_2_value") = player->actionPoints();
            *_labels.at("params_3_value") = player->carryWeightMax();
            *_labels.at("params_4_value") = player->meleeDamage();
            *_labels.at("params_5_value") = player->damageResistance();
            *_labels.at("params_5_value")+= "%";
            *_labels.at("params_6_value") = player->poisonResistance();
            *_labels.at("params_6_value")+= "%";
            *_labels.at("params_7_value") = player->radiationResistance();
            *_labels.at("params_7_value")+= "%";
            *_labels.at("params_8_value") = player->sequence();
            *_labels.at("params_9_value") = player->healingRate();
            *_labels.at("params_10_value") = player->criticalChance();
            *_labels.at("params_10_value")+= "%";

            // Stats counters and labels
            for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
            {
                std::stringstream ss;
                ss << "stats_" << (i+1);
                unsigned int val = player->statTotal((STAT)i);
                _counters.at(ss.str())->setNumber(val);
                _counters.at(ss.str())->setColor(UI::BigCounter::Color::WHITE);
                if (val > 10)
                {
                    val = 10;
                    _counters.at(ss.str())->setColor(UI::BigCounter::Color::RED);
                }
                _labels.at(ss.str())->setText(_t(MSG_STATS, 300 + (val < 1 ? 1 : val)));
            }

            // Skills values
            for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
            {
                std::stringstream ss;
                ss << "skills_" << (i + 1) << "_value";
                *_labels.at(ss.str()) = player->skillValue((SKILL)i);
                *_labels.at(ss.str())+= "%";
            }

            // Default labels colors
            for(auto it = _labels.begin(); it != _labels.end(); ++it)
            {
                std::string name = it->first;

                Graphics::Color font1_3ff800ff = {0x3f, 0xf8, 0x00, 0xff};
                Graphics::Color font1_a0a0a0ff = {0xa0, 0xa0, 0xa0, 0xff};
                Graphics::Color font1_183018ff = {0x18, 0x30, 0x18, 0xff};

                if (name.find("stats_") == 0 || name.find("params_") == 0) {
                    it->second->setColor(font1_3ff800ff);
                }

                if (name.find("skills_") == 0) {
                    unsigned number = atoi(name.substr(7).c_str()) - 1;
                    it->second->setColor(player->skillTagged((SKILL)number) ? font1_a0a0a0ff : font1_3ff800ff);
                }

                if (name.find("health_") == 0) {
                    it->second->setColor(name.compare("health_1") == 0 ? font1_3ff800ff : font1_183018ff);
                }
            }

            // Selected labels colors
            for(auto it = _labels.begin(); it != _labels.end(); ++it) {
                if (_selectedLabel != it->second) {
                    continue;
                }

                std::string name = it->first;

                _title->setText(_titles.at(name));
                _description->setText(_descriptions.at(name));

                _selectedImage  = _images.at(name);

                Graphics::Color font1_ffff7fff = {0xff, 0xff, 0x7f, 0xff};
                Graphics::Color font1_ffffffff = {0xff, 0xff, 0xff, 0xff};
                Graphics::Color font1_707820ff = {0x70, 0x78, 0x20, 0xff};

                if (name.find("stats_") == 0) {
                    it->second->setColor(font1_ffff7fff);
                }

                if (name.find("params_") == 0) {
                    it->second->setColor(font1_ffff7fff);
                    _labels.at(name+"_value")->setColor(font1_ffff7fff);
                }

        //        if (name.find("traits_") == 0)
        //        {
        //            unsigned int number = atoi(name.substr(7).c_str());
        //            it->second->setColor(player->trait(number - 1) ? font1_ffffffff : font1_ffff7fff);
        //        }

                if (name.find("skills_") == 0) {
                    unsigned number = atoi(name.substr(7).c_str()) - 1;
                    it->second->setColor(player->skillTagged((SKILL)number) ? font1_ffffffff : font1_ffff7fff);
                    _labels.at(name+"_value")->setColor(player->skillTagged((SKILL)number) ? font1_ffffffff : font1_ffff7fff);
                }

                if (name.find("health_") == 0) {
                    it->second->setColor(name.compare("health_1") == 0 ? font1_ffff7fff : font1_707820ff);
                }
            }

        }

        void PlayerEdit::_onButtonClick(std::shared_ptr<UI::ImageButton> target) {
            for (auto it = _buttons.begin(); it != _buttons.end(); ++it) {
                if (it->second == target) {
                    std::string name = it->first;

                    if (name == "cancel") {
                        return doCancel();
                    }
                    if (name == "done") {
                        return doDone();
                    }
                }
            }
        }

        void PlayerEdit::onLabelClick(std::shared_ptr<UI::TextArea> target)
        {
            for (auto it = _labels.begin(); it != _labels.end(); ++it) {
                std::string name = it->first;
                if (it->second == target) {
                    // name.find("traits_") == 0 ||
                    if (name.find("stats_") == 0 || name.find("skills_") == 0 || name.find("health_") == 0 || name.find("params_") == 0 || name.find("label_") == 0 || name.find("level_") == 0 ) {
                        std::string label = name;
                        if (name.find("_value") > 0) {
                            label = name.substr(0, name.find("_value"));
                        }
                        _selectedLabel = _labels.at(label.c_str());

                        _selectedImage  = _images.at(label.c_str());
                    }
                }
            }
        }

        void PlayerEdit::onMaskClick(std::shared_ptr<UI::HiddenMask> target)
        {
            for(auto it = _masks.begin(); it != _masks.end(); ++it)
            {
                if (it->second == target)
                {
                    std::string name = it->first;
                    if (name.find("stats_") == 0)
                    {
                        _selectedLabel = _labels.at(name);

                        _selectedImage = _images.at(name);
                    }
                }
            }
        }

        /**
         * Switching between tabs
         * PERKS = 0, KARMA = 1, KILLS = 2
         */
        void PlayerEdit::onTabClick(Event::Mouse* event)
        {
            auto tabs = getUI<UI::ImageList>("tabs");
            unsigned int clickX = static_cast<unsigned>(event->position().x() - tabs->position().x());

            for (unsigned int i = 0, tabEnd = 0; i < 3; i++) {
                unsigned int tabStart = tabEnd;
                // selected width = 120, unselected width = 100
                tabEnd += (i == tabs->currentImage() ? 120 : 100);

                auto tab = getUI<UI::TextArea>("tab_" + std::to_string(i));
                const auto tabsY = tabs->position().y() + 7;

                // Slightly raise the selected tab and lower the others
                if (tabStart <= clickX && clickX <= tabEnd) {
                    tabs->setCurrentImage(i);
                    tab->setPosition({ tab->position().x(), tabsY - 1 });
                } else {
                    tab->setPosition({ tab->position().x(), tabsY + 1 });
                }
            }

            getUI<UI::TextArea>("tab_perks")->setVisible(tabs->currentImage() == 0);
            getUI<UI::TextArea>("tab_karma")->setVisible(tabs->currentImage() == 1);
            getUI<UI::TextAreaList>("tab_kills_enemies")->setVisible(tabs->currentImage() == 2);
            getUI<UI::TextAreaList>("tab_kills_score")->setVisible(tabs->currentImage() == 2);
        }

        void PlayerEdit::doCancel()
        {
            Game::Game::getInstance()->popState();
        }

        void PlayerEdit::doDone()
        {
            Game::Game::getInstance()->popState();
        }

        void PlayerEdit::doPrint()
        {
            // @TODO: implement
        }

        void PlayerEdit::onStateActivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void PlayerEdit::onStateDeactivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->popState();
        }

        void PlayerEdit::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_c:
                    doCancel();
                    break;
                case SDLK_RETURN:
                case SDLK_d:
                    doDone();
                    break;
                case SDLK_p:
                    doPrint();
                    break;
            }
        }

        void PlayerEdit::render()
        {
            State::render();
            auto background = getUI<UI::Image>("bg");
            Point backgroundPos = Point((Game::Game::getInstance()->renderer()->size() - background->size()) / 2);
            _selectedImage->setPosition(backgroundPos + Point(480, 310));
            _selectedImage->render();
            _description->setPosition(backgroundPos + Point(350, 315));
            _description->render();
        }
    }
}
