#include <ctype.h>

#include "../State/PlayerChoosePerk.h"
#include "../State/PlayerEdit.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../UI/TextArea.h"
#include "../UI/TextAreaList.h"
#include "../UI/ImageButton.h"
#include "../UI/Image.h"
#include "../UI/Rectangle.h"

namespace Falltergeist
{
    namespace State
    {
        PlayerChoosePerk::PlayerChoosePerk() : State()
        {
            _bgPos = Point((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
        }

        PlayerChoosePerk::~PlayerChoosePerk()
        {
        }

        void PlayerChoosePerk::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);

            int bgX = _bgPos.x();
            int bgY = _bgPos.y();

            auto bg = new UI::Image("art/intrface/perkwin.frm");
            bg->setPosition(_bgPos + Point(30, 95));

            auto pickPerkLabel = new UI::TextArea(_t(MSG_EDITOR, 152), bgX+80, bgY+112);
            pickPerkLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+78, bgY+282);
            doneButton->mouseClickHandler().add(std::bind(&PlayerChoosePerk::onDoneButtonClick, this, std::placeholders::_1));

            auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX+98, bgY+282);
            doneLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            auto cancelButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+183, bgY+282);
            cancelButton->mouseClickHandler().add(std::bind(&PlayerChoosePerk::onCancelButtonClick, this, std::placeholders::_1));

            auto cancelLabel = new UI::TextArea(_t(MSG_EDITOR, 102), bgX+203, bgY+282);
            cancelLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            _perkNames = new UI::TextAreaList(_bgPos + Point(78, 137));
            _perkRanks = new UI::TextAreaList(_bgPos + Point(240,137));
            _perkNames->setSize({ 0, 140 });
            _perkRanks->setSize({ 0, 140 });

            auto scrollUp = new UI::ImageButton(UI::ImageButton::Type::SMALL_UP_ARROW, bgX+55, bgY+140);
            scrollUp->mouseClickHandler().add([=](...) {
                if (--_selectedIndex < 0) _selectedIndex = 0;

                _perkNames->scrollUp();
                _perkRanks->scrollUp();

                selectPerk(_selectedIndex);
            });

            auto scrollDown = new UI::ImageButton(UI::ImageButton::Type::SMALL_DOWN_ARROW, bgX+55, bgY+153);
            scrollDown->mouseClickHandler().add([=](...) {
                int limit = static_cast<int>(_perkNames->textAreas().size()) - 1;
                if (++_selectedIndex > limit) _selectedIndex = limit;

                _perkNames->scrollDown();
                _perkRanks->scrollDown();

                selectPerk(_selectedIndex);
            });


            _title = new UI::TextArea("", _bgPos + Point(310, 125));
            _title->setFont("font2.aaf", {0,0,0,0xff});

            auto line = new UI::Rectangle(_bgPos + Point(310, 155), Graphics::Size(270, 2), { 0x00, 0x00, 0x00, 0xff });

            _description = new UI::TextArea("", _bgPos + Point(310, 170));
            _description->setFont("font1.aaf", {0,0,0,0xff});
            _description->setSize({140, 120});
            _description->setWordWrap(true);

            addUI(bg);

            // Selected perk info
            addUI(_title);
            addUI(line);
            addUI(_description);

            addUI(pickPerkLabel);
            addUI(scrollUp);
            addUI(scrollDown);
            addUI(_perkNames);
            addUI(_perkRanks);
            addUI(doneButton);
            addUI(doneLabel);
            addUI(cancelLabel);
            addUI(cancelButton);

            auto player = Game::getInstance()->player();

            auto selectablePerks = dynamic_cast<PlayerEdit*>(Game::getInstance()->topState(1))->getSelectablePerks();

            // Populate the TextAreaList containing perks
            for (const auto &perk : selectablePerks) {
                int currentRank = player->perk(perk.perk);

                if (currentRank < perk.maxRank && player->level() >= perk.minLevel && perk.otherRequirements()) {

                    auto perkLabel = std::make_unique<UI::TextArea>(_t(MSG_PERK, 101 + static_cast<unsigned>(perk.perk)));
                    perkLabel->mouseClickHandler().add([=](...) {
                        // TODO: TextAreaList doesn't support mouse input events for its child items
                    });
                    _perkNames->addArea(std::move(perkLabel));

                    _perkRanks->addArea(std::make_unique<UI::TextArea>(currentRank > 0 ? "(" + std::to_string(currentRank) + ")" : " "));

                    _perksList.push_back(perk.perk);

                    _images.push_back(std::make_shared<UI::Image>("art/skilldex/" + perk.image + ".frm"));
                }
            }

            selectPerk(0);
        }

        void PlayerChoosePerk::render()
        {
            State::render();
            _selectedImage->render();
        }

        void PlayerChoosePerk::selectPerk(int index)
        {
            for (unsigned i = 0; i < _perkNames->textAreas().size(); i++) {
                if (i == static_cast<unsigned>(index)) {
                    _perkNames->textAreas().at(i)->setColor({0xff, 0xff, 0x7f, 0xff}); // yellow
                    _perkRanks->textAreas().at(i)->setColor({0xff, 0xff, 0x7f, 0xff}); // yellow

                    _selectedPerk = _perksList.at(i);
                    unsigned perkIndex = static_cast<unsigned>(_perksList.at(i));
                    _title->setText(_t(MSG_PERK, 101 + perkIndex));
                    _description->setText(_t(MSG_PERK, 1101 + perkIndex));
                    _selectedImage = _images.at(i);
                    _selectedImage->setPosition(_bgPos + Point(450, 160));
                } else {
                    _perkNames->textAreas().at(i)->setColor({0x3f, 0xf8, 0x00, 0xff}); // green
                    _perkRanks->textAreas().at(i)->setColor({0x3f, 0xf8, 0x00, 0xff}); // green
                }
            }
        }

        void PlayerChoosePerk::onDoneButtonClick(Event::Mouse*)
        {
            Game::getInstance()->player()->addPerk(_selectedPerk);
            auto perksTab = dynamic_cast<UI::TextAreaList*>(Game::getInstance()->topState(1)->getUI("tab_perks"));
            perksTab->addArea(std::make_unique<UI::TextArea>(_t(MSG_PERK, 101 + static_cast<unsigned>(_selectedPerk))));
            Game::getInstance()->popState();
        }

        void PlayerChoosePerk::onCancelButtonClick(Event::Mouse*)
        {
            Game::getInstance()->popState();
        }
    }
}
