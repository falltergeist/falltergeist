#include "../State/SettingsMenu.h"

#include "../Audio/Mixer.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/MultistateImageButton.h"
#include "../UI/Slider.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        SettingsMenu::SettingsMenu(std::shared_ptr<UI::IResourceManager> _resourceManager) :
            State{},
            resourceManager{std::move(_resourceManager)},
            imageButtonFactory{std::make_unique<UI::Factory::ImageButtonFactory>(resourceManager)}
        {
        }

        void SettingsMenu::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);

            // background
            auto background = resourceManager->getImage("art/intrface/prefscrn.frm");
            Point backgroundPos = Point((Game::getInstance()->renderer()->size() - background->size()) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();
            background->setPosition(backgroundPos);
            addUI(background);

            auto settings = Game::getInstance()->settings();

            // Switches (big)
            {
                auto combatDifficultySwitch = makeNamedUI<UI::MultistateImageButton>(
                        "combat_difficulty",
                        UI::MultistateImageButton::Type::BIG_SWITCH,
                        backgroundPos.add(76, 149));
                combatDifficultySwitch->setMaxState(3);
                combatDifficultySwitch->setState(settings->combatDifficulty());
            }

            {
                auto gameDifficultySwitch = makeNamedUI<UI::MultistateImageButton>(
                        "game_difficulty",
                        UI::MultistateImageButton::Type::BIG_SWITCH,
                        backgroundPos.add(76, 71));
                gameDifficultySwitch->setMaxState(3);
                gameDifficultySwitch->setState(settings->gameDifficulty());
            }

            {
                auto violenceLevelSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "violence_level",
                        UI::MultistateImageButton::Type::BIG_SWITCH,
                        backgroundPos.add(76, 227));
                violenceLevelSwitch->setState(settings->violenceLevel());
                addUI("violence_level", violenceLevelSwitch);
            }

            {
                auto targetHighlightSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "target_highlight",
                        UI::MultistateImageButton::Type::BIG_SWITCH,
                        backgroundPos.add(76, 309));
                targetHighlightSwitch->setMaxState(3);
                targetHighlightSwitch->setState(settings->targetHighlight());
            }

            {
                auto combatLooksSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "combat_looks",
                        UI::MultistateImageButton::Type::BIG_SWITCH,
                        Point{backgroundX + 76, backgroundY + 387});
                combatLooksSwitch->setMaxState(2);
                combatLooksSwitch->setState(settings->combatLooks());
            }

            // Switches (small)

            {
                auto combatMessagesSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "combat_messages",
                        UI::MultistateImageButton::Type::SMALL_SWITCH,
                        Point{backgroundX + 299, backgroundY + 74});
                combatMessagesSwitch->setState(settings->combatMessages());
            }

            {
                auto combatTauntsSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "combat_taunts",
                        UI::MultistateImageButton::Type::SMALL_SWITCH,
                        Point{backgroundX + 299, backgroundY + 74 + 66});
                combatTauntsSwitch->setState(settings->combatTaunts());
            }

            {
                auto languageFilterSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "language_filter",
                        UI::MultistateImageButton::Type::SMALL_SWITCH,
                        Point{backgroundX+299, backgroundY + 74 + 66 * 2});
                languageFilterSwitch->setState(settings->languageFilter());
            }

            {
                auto runningSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "running",
                        UI::MultistateImageButton::Type::SMALL_SWITCH,
                        Point{backgroundX + 299, backgroundY + 74 + 66 * 3});
                runningSwitch->setState(settings->running());
            }

            {
                auto subtitlesSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "subtitles",
                        UI::MultistateImageButton::Type::SMALL_SWITCH,
                        Point{backgroundX + 299, backgroundY + 74 + 66 * 4});
                subtitlesSwitch->setState(settings->subtitles());
            }

            {
                auto itemHightlightSwitch = makeNamedUI<UI::MultistateImageButton>(
                        "item_highlight",
                        UI::MultistateImageButton::Type::SMALL_SWITCH,
                        Point{backgroundX + 299, backgroundY + 74 + 66 * 5});
                itemHightlightSwitch->setState(settings->itemHighlight());
            }

            // LABELS
            SDL_Color color = {0x90, 0x78, 0x24, 0xff};

            std::string font1_907824ff = "font1.aaf";
            std::string font3_907824ff = "font3.aaf";
            std::string font4_907824ff = "font4.aaf";

            // GAME PREFERENCES
            _addTextArea(_t(MSG_OPTIONS, 100), backgroundX+74, backgroundY+10)->setFont(font4_907824ff, color);

            // COMBAT DIFFICULTY
            auto difficulty = _addTextArea(_t(MSG_OPTIONS, 101), backgroundX+21, backgroundY+48);
            difficulty->setWidth(158);
            difficulty->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            difficulty->setFont(font3_907824ff, color);

            // GAME DIFFICULTY
            _addTextArea(difficulty, backgroundX+21, backgroundY+48+77)->setText(_t(MSG_OPTIONS, 102));

            // VIOLENCE LEVEL
            _addTextArea(difficulty, backgroundX+21, backgroundY+48+156)->setText(_t(MSG_OPTIONS, 103));

            // TARGET HIGHLIGHT
            _addTextArea(difficulty, backgroundX+21, backgroundY+128+158)->setText(_t(MSG_OPTIONS, 104));

            // COMBAT LOOKS
            _addTextArea(difficulty, backgroundX+21, backgroundY+128+235)->setText(_t(MSG_OPTIONS, 105));

            // COMBAT MESSAGES
            auto combatMessages = _addTextArea(_t(MSG_OPTIONS, 106), backgroundX+206, backgroundY+49);
            combatMessages->setFont(font3_907824ff, color);

            // COMBAT TAUNTS
            _addTextArea(combatMessages, backgroundX+206, backgroundY+49+66)->setText(_t(MSG_OPTIONS, 107));

            // LANGUAGE FILTER
            _addTextArea(combatMessages, backgroundX+206, backgroundY+49+66*2)->setText(_t(MSG_OPTIONS, 108));

            // RUNNING
            _addTextArea(combatMessages, backgroundX+206, backgroundY+49+66*3)->setText(_t(MSG_OPTIONS, 109));

            // SUBTITLES
            _addTextArea(combatMessages, backgroundX+206, backgroundY+49+66*4)->setText(_t(MSG_OPTIONS, 110));

            // ITEM HIGHLIGHT
            _addTextArea(combatMessages, backgroundX+206, backgroundY+49+66*5)->setText(_t(MSG_OPTIONS, 111));

            // COMBAT SPEED
            auto combatSpeed = _addTextArea(_t(MSG_OPTIONS, 112), backgroundX+384, backgroundY+19);
            combatSpeed->setFont(font3_907824ff, color);

            // TEXT DELAY
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+95)->setText(_t(MSG_OPTIONS, 113));

            // MASTER AUDIO VOLUME
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+165)->setText(_t(MSG_OPTIONS, 114));

            // MUSIC/MOVIE VOLUME
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+165+51)->setText(_t(MSG_OPTIONS, 115));

            // SOUND EFFECTS VOLUME
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+165+51*2)->setText(_t(MSG_OPTIONS, 116));

            // SPEECH VOLUME
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+165+51*3)->setText(_t(MSG_OPTIONS, 117));

            // BRIGHTNESS LEVEL
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+165+51*4)->setText(_t(MSG_OPTIONS, 118));

            // MOUSE SENSITIVITY
            _addTextArea(combatSpeed, backgroundX+384, backgroundY+165+51*5)->setText(_t(MSG_OPTIONS, 119));

            // DEFAULT BUTTON LABEL
            auto label = _addTextArea(combatSpeed, backgroundX+43, backgroundY+449);
            label->setText(_t(MSG_OPTIONS, 120));
            label->setFont(font3_907824ff, color);

            // DONE BUTTON LABEL
            label = _addTextArea(combatSpeed, backgroundX+169, backgroundY+449);
            label->setText(_t(MSG_OPTIONS, 300));
            label->setFont(font3_907824ff, color);

            // CANCEL BUTTON LABEL
            label = _addTextArea(combatSpeed, backgroundX+283, backgroundY+449);
            label->setText(_t(MSG_OPTIONS, 121));
            label->setFont(font3_907824ff, color);

            // COMBAT DIFFICULTY SWITCH LABELS
            _addTextArea(_t(MSG_OPTIONS, 203), backgroundX+50, backgroundY+81)->setFont(font1_907824ff, color);     // EASY
            _addTextArea(_t(MSG_OPTIONS, 204), backgroundX+81, backgroundY+67)->setFont(font1_907824ff, color);     // NORMAL
            _addTextArea(_t(MSG_OPTIONS, 205), backgroundX+122, backgroundY+81)->setFont(font1_907824ff, color);    // HARD

            // GAME DIFFICULTY SWITCH LABELS
            _addTextArea(_t(MSG_OPTIONS, 206), backgroundX+45, backgroundY+159)->setFont(font1_907824ff, color);    // WIMPY
            _addTextArea(_t(MSG_OPTIONS, 207), backgroundX+83, backgroundY+145)->setFont(font1_907824ff, color);    // NORMAL
            _addTextArea(_t(MSG_OPTIONS, 208), backgroundX+122, backgroundY+159)->setFont(font1_907824ff, color);   // ROUGH

            // VIOLENCE LEVEL SWITCH LABELS
            _addTextArea(_t(MSG_OPTIONS, 214), backgroundX+48, backgroundY+236)->setFont(font1_907824ff, color);    // NONE
            _addTextArea(_t(MSG_OPTIONS, 215), backgroundX+83, backgroundY+222)->setFont(font1_907824ff, color);    // MINIMUM
            _addTextArea(_t(MSG_OPTIONS, 207), backgroundX+122, backgroundY+236)->setFont(font1_907824ff, color);   // NORMAL
            label = _addTextArea(_t(MSG_OPTIONS, 216).insert(8, " "), backgroundX+122, backgroundY+257);
            label->setFont(font1_907824ff, color);
            label->setWidth(50);
            label->setWordWrap(true); // MAXIMUM BLOOD

            // TARGET HIGHLIGHT SWITCH LABELS
            _addTextArea(_t(MSG_OPTIONS, 202), backgroundX+59, backgroundY+319)->setFont(font1_907824ff, color);    // OFF
            _addTextArea(_t(MSG_OPTIONS, 201), backgroundX+95, backgroundY+305)->setFont(font1_907824ff, color);    // ON
            label = _addTextArea(_t(MSG_OPTIONS, 213).insert(10, " "), backgroundX+122, backgroundY+319);
            label->setFont(font1_907824ff, color);
            label->setWidth(60);
            label->setWordWrap(true); // TARGETING ONLY

            // COMBAT LOOKS SWITCH LABELS
            _addTextArea(_t(MSG_OPTIONS, 202), backgroundX+59, backgroundY+397)->setFont(font1_907824ff, color);    // OFF
            _addTextArea(_t(MSG_OPTIONS, 201), backgroundX+95, backgroundY+383)->setFont(font1_907824ff, color);    // ON

            // COMBAT MESSAGES SWITCH LABELS
            auto verboseLabel = _addTextArea(_t(MSG_OPTIONS, 211), backgroundX+203, backgroundY+69);         // VERBOSE
            verboseLabel->setFont(font1_907824ff, color);
            verboseLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            verboseLabel->setWidth(100);
            _addTextArea(_t(MSG_OPTIONS, 212), backgroundX+320, backgroundY+69)->setFont(font1_907824ff, color);    // BRIEF

            // COMBAT TAUNTS SWITCH LABELS
            _addTextArea(verboseLabel, backgroundX+203, backgroundY+69+67)->setText(_t(MSG_OPTIONS, 202)); // OFF
            _addTextArea(_t(MSG_OPTIONS, 201), backgroundX+320, backgroundY+69+67)->setFont(font1_907824ff, color); // ON

            // LANGUAGE FILTER SWITCH LABELS
            _addTextArea(verboseLabel, backgroundX+203, backgroundY+69+67+66)->setText(_t(MSG_OPTIONS, 202)); // OFF
            _addTextArea(_t(MSG_OPTIONS, 201), backgroundX+320, backgroundY+69+67+66)->setFont(font1_907824ff, color); // ON

            // RUNNING SWITCH LABELS
            _addTextArea(verboseLabel, backgroundX+203, backgroundY+69+67+66+64)->setText(_t(MSG_OPTIONS, 209)); // NORMAL
            _addTextArea(_t(MSG_OPTIONS, 219), backgroundX+320, backgroundY+69+67+66+64)->setFont(font1_907824ff, color); // ALWAYS

            // SUBTITLES SWITCH LABELS
            _addTextArea(verboseLabel, backgroundX+203, backgroundY+69+67+66+66+65)->setText(_t(MSG_OPTIONS, 202)); // OFF
            _addTextArea(_t(MSG_OPTIONS, 201), backgroundX+320, backgroundY+69+66+67+66+65)->setFont(font1_907824ff, color); // OFF

            // ITEM HIGHLIGHT SWITCH LABELS
            _addTextArea(verboseLabel, backgroundX+203, backgroundY+69+67+66+64+65+68)->setText(_t(MSG_OPTIONS, 202)); // OFF
            _addTextArea(_t(MSG_OPTIONS, 201), backgroundX+320, backgroundY+69+64+67+66+65+68)->setFont(font1_907824ff, color); // ON

            // AFFECT PLAYER SPEECH
            _addTextArea(_t(MSG_OPTIONS, 122), backgroundX+405, backgroundY+72)->setFont(font1_907824ff, color);

            // COMBAT SPEED SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+384, backgroundY+38)->setFont(font1_907824ff, color);      // NORMAL
            auto fastestLabel = _addTextArea(_t(MSG_OPTIONS, 210), backgroundX+524, backgroundY+38);           // FASTEST
            fastestLabel->setFont(font1_907824ff, color);
            fastestLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            fastestLabel->setWidth(100);

            // TEXT DELAY SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 217), backgroundX+384, backgroundY+113)->setFont(font1_907824ff, color);     // SLOW
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+484, backgroundY+113)->setFont(font1_907824ff, color);     // NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+113)->setText(_t(MSG_OPTIONS, 218));       // FASTER

            // MASTER AUDIO VOLUME SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 202), backgroundX+384, backgroundY+184)->setFont(font1_907824ff, color);     // OFF
            _addTextArea(_t(MSG_OPTIONS, 221), backgroundX+452, backgroundY+184)->setFont(font1_907824ff, color);     // QUIET
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+521, backgroundY+184)->setFont(font1_907824ff, color);     // NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+184)->setText(_t(MSG_OPTIONS, 222));       // LOUD

            // MUSIC/MOVIE VOLUME SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 202), backgroundX+384, backgroundY+184+51)->setFont(font1_907824ff, color);  // OFF
            _addTextArea(_t(MSG_OPTIONS, 221), backgroundX+452, backgroundY+184+51)->setFont(font1_907824ff, color);  // QUIET
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+521, backgroundY+184+51)->setFont(font1_907824ff, color);  // NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+184+51)->setText(_t(MSG_OPTIONS, 222));    // LOUD

            // SOUND EFFECTS SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 202), backgroundX+384, backgroundY+184+51*2)->setFont(font1_907824ff, color);// OFF
            _addTextArea(_t(MSG_OPTIONS, 221), backgroundX+452, backgroundY+184+51*2)->setFont(font1_907824ff, color);// QUIET
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+521, backgroundY+184+51*2)->setFont(font1_907824ff, color);// NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+184+51*2)->setText(_t(MSG_OPTIONS, 222));  // LOUD

            // SPEECH VOLUME SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 202), backgroundX+384, backgroundY+184+51*3)->setFont(font1_907824ff, color);// OFF
            _addTextArea(_t(MSG_OPTIONS, 221), backgroundX+452, backgroundY+184+51*3)->setFont(font1_907824ff, color);// QUIET
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+521, backgroundY+184+51*3)->setFont(font1_907824ff, color);// NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+184+51*3)->setText(_t(MSG_OPTIONS, 222));  // LOUD

            // BRIGHTNESS LEVEL SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+384, backgroundY+184+51*4)->setFont(font1_907824ff, color);// NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+184+51*4)->setText(_t(MSG_OPTIONS, 223));  // BRIGHTER

            // MOUSE SENSITIVITY SLIDER LABELS
            _addTextArea(_t(MSG_OPTIONS, 209), backgroundX+384, backgroundY+184+51*5)->setFont(font1_907824ff, color);// NORMAL
            _addTextArea(fastestLabel, backgroundX+524, backgroundY+184+51*5)->setText(_t(MSG_OPTIONS, 218));  // FASTER

            // BUTTONS

            // button: Default
            {
                auto defaultButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 23, backgroundY + 450});
                defaultButton->mouseClickHandler().add(std::bind(&SettingsMenu::onDefaultButtonClick, this, std::placeholders::_1));
                addUI(std::move(defaultButton));
            }

            // button: Done
            {
                auto doneButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 148, backgroundY + 450});
                doneButton->mouseClickHandler().add([this](Event::Event* event){ this->doSave(); });
                addUI(std::move(doneButton));
            }

            // button: Cancel
            {
                auto cancelButton = imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {backgroundX + 263, backgroundY + 450});
                cancelButton->mouseClickHandler().add([this](Event::Event* event){ this->doCancel(); });
                addUI(std::move(cancelButton));
            }

            // button: Affect player speed
            {
                auto affectPlayerSpeedCheckBox = imageButtonFactory->getByType(ImageButtonType::CHECKBOX, {backgroundX + 383, backgroundY + 68});
                affectPlayerSpeedCheckBox->setChecked(settings->playerSpeedup());
                addUI("player_speedup", std::move(affectPlayerSpeedCheckBox));
            }

            // SLIDERS
            // COMBAT SPEED SLIDER
            {
                auto combatSpeedSlider = makeNamedUI<UI::Slider>(
                        "combat_speed",
                        backgroundPos.add(384, 50),
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                combatSpeedSlider->setMinValue(0.0);
                combatSpeedSlider->setMaxValue(50.0);
                combatSpeedSlider->setValue(settings->combatSpeed());
            }


            // TEXT DELAY SLIDER
            {
                auto textDelaySlider = makeNamedUI<UI::Slider>(
                        "text_delay",
                        Point{backgroundX + 384, backgroundY + 125},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                textDelaySlider->setValue(settings->textDelay());
            }

            // MASTER AUDIO VOLUME SLIDER
            {
                auto masterAudioVolumeSlider = makeNamedUI<UI::Slider>(
                        "master_volume",
                        Point{backgroundX + 384, backgroundY + 196},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                masterAudioVolumeSlider->setValue(settings->masterVolume());
            }

            // MUSIC VOLUME SLIDER
            {
                auto musicVolumeSlider = makeNamedUI<UI::Slider>(
                        "music_volume",
                        Point{backgroundX + 384, backgroundY + 196 + 51},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                musicVolumeSlider->setValue(settings->musicVolume());
                musicVolumeSlider->changeHandler().add([=](Event::Event* evt) {
                    Game::getInstance()->mixer()->setMusicVolume(musicVolumeSlider->value());
                });
            }

            // SOUND EFFECTS VOLUME SLIDER
            {
                auto soundEffectsVolumeSlider = makeNamedUI<UI::Slider>(
                        "sfx_volume",
                        Point{backgroundX + 384, backgroundY + 196 + 51 * 2},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                soundEffectsVolumeSlider->setValue(settings->sfxVolume());
            }

            // SPEECH VOLUME SLIDER
            {
                auto speechVolumeSlider = makeNamedUI<UI::Slider>(
                        "voice_volume",
                        Point{backgroundX + 384, backgroundY + 196 + 51 * 3},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                speechVolumeSlider->setValue(settings->voiceVolume());
            }

            // BRIGHTNESS LEVEL SLIDER
            {
                auto brightnessLevelSlider = makeNamedUI<UI::Slider>(
                        "brightness",
                        Point{backgroundX + 384, backgroundY + 196 + 51 * 4},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                brightnessLevelSlider->setValue(settings->brightness());
            }

            // MOUSE SENSITIVITY SLIDER
            {
                auto mouseSensitivitySlider = makeNamedUI<UI::Slider>(
                        "mouse_sensitivity",
                        Point{backgroundX + 384, backgroundY + 196 + 51 * 5},
                        resourceManager->getImage("art/intrface/prfsldon.frm"),
                        resourceManager->getImage("art/intrface/prfsldof.frm")
                );
                mouseSensitivitySlider->setValue(settings->mouseSensitivity());
            }
        }

        //IniFileSection SettingsMenu::_getSettings()
        //{
        //    // @todo Load options from FALLTERGEIST_DATA/config.ini if exists
        //
        //    // or return default values
        //    return _getDefaultSettings();
        //}
        //
        //IniFileSection SettingsMenu::_getDefaultSettings()
        //{
        //    return IniFileSection({
        //        {       "brightness", "1.000000"}, // max 1.179993
        //        {"combat_difficulty", "1"},
        //        {     "combat_looks", "0"},
        //        {  "combat_messages", "1"},
        //        {     "combat_speed", "0"},
        //        {    "combat_taunts", "1"},
        //        {  "game_difficulty", "1"},
        //        {   "item_highlight", "1"},
        //        {  "language_filter", "0"},
        //        {"mouse_sensitivity", "1.000000"},  // max 2.500000
        //        {   "player_speedup", "0"},
        //        {          "running", "0"},
        //        {        "subtitles", "0"},
        //        { "target_highlight", "2"},
        //        {  "text_base_delay", "3.500000"},  // max 1.000000
        //        {  "text_line_delay", "1.000000"},  // max 0.000000
        //        {   "violence_level", "3"}
        //    });
        //}

        std::shared_ptr<UI::TextArea> SettingsMenu::_addLabel(const std::string& name, std::shared_ptr<UI::TextArea> label)
        {
            _labels.insert(std::make_pair(name, label));
            return label;
        }

        std::shared_ptr<UI::TextArea> SettingsMenu::_addTextArea(const std::string& message, unsigned int x, unsigned int y)
        {
            auto textArea = makeUI<UI::TextArea>(message, x, y);
            addUI(textArea);
            return textArea;
        }

        std::shared_ptr<UI::TextArea> SettingsMenu::_addTextArea(std::shared_ptr<UI::TextArea> parent, unsigned int x, unsigned int y)
        {
            auto textArea = makeUI<UI::TextArea>(*parent, Point(x, y));
            addUI(textArea);
            return textArea;
        }

        void SettingsMenu::doCancel()
        {
            // TODO: restore volume and mouse sensitivity
            Game::getInstance()->popState();
        }

        void SettingsMenu::doSave()
        {
            auto settings = Game::getInstance()->settings();
            settings->setCombatDifficulty(getUI<UI::MultistateImageButton>("combat_difficulty")->state());
            settings->setGameDifficulty(getUI<UI::MultistateImageButton>("game_difficulty")->state());
            settings->setViolenceLevel(getUI<UI::MultistateImageButton>("violence_level")->state());
            settings->setTargetHighlight(getUI<UI::MultistateImageButton>("target_highlight")->state());
            settings->setCombatLooks(getUI<UI::MultistateImageButton>("combat_looks")->state());
            settings->setCombatMessages(getUI<UI::MultistateImageButton>("combat_messages")->state());
            settings->setCombatTaunts(getUI<UI::MultistateImageButton>("combat_taunts")->state());
            settings->setLanguageFilter(getUI<UI::MultistateImageButton>("language_filter")->state());
            settings->setRunning(getUI<UI::MultistateImageButton>("running")->state());
            settings->setSubtitles(getUI<UI::MultistateImageButton>("subtitles")->state());
            settings->setItemHighlight(getUI<UI::MultistateImageButton>("item_highlight")->state());

            settings->setMasterVolume(getUI<UI::Slider>("master_volume")->value());
            settings->setMusicVolume(getUI<UI::Slider>("music_volume")->value());
            settings->setVoiceVolume(getUI<UI::Slider>("voice_volume")->value());
            settings->setSfxVolume(getUI<UI::Slider>("sfx_volume")->value());

            settings->setTextDelay(getUI<UI::Slider>("text_delay")->value());
            settings->setCombatSpeed(static_cast<unsigned>(getUI<UI::Slider>("combat_speed")->value()));
            settings->setBrightness(getUI<UI::Slider>("brightness")->value());
            settings->setMouseSensitivity(getUI<UI::Slider>("mouse_sensitivity")->value());

            settings->setPlayerSpeedup(getUI<UI::ImageButton>("player_speedup")->checked());

            settings->save();
            Game::getInstance()->popState();
        }

        void SettingsMenu::onDefaultButtonClick(Event::Mouse* event)
        {
        }

        void SettingsMenu::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    doCancel();
                    break;
                case SDLK_RETURN:
                    doSave();
                    break;
            }
        }

        void SettingsMenu::onStateActivate(Event::State* event)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void SettingsMenu::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }
    }
}
