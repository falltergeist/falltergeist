#include "../State/Movie.h"
#include "../Audio/Mixer.h"
#include "../CrossPlatform.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Format/Lst/File.h"
#include "../Format/Sve/File.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Ini/File.h"
#include "../Ini/Parser.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/State.h"
#include "../State/MainMenu.h"
#include "../UI/MvePlayer.h"
#include "../UI/TextArea.h"
#include "../Exception.h"

namespace Falltergeist
{
    namespace State
    {
        using Point = Graphics::Point;
        using Cursor = Input::Mouse::Cursor;

        Movie::Movie(std::shared_ptr<Input::Mouse> mouse, int id) : State(mouse), _id(id) {
        }

        Movie::~Movie()
        {
        }

        void Movie::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(true);
            setModal(true);

            auto renderer = Game::Game::getInstance()->renderer();
            setPosition((renderer->size() - Point(640, 320)) / 2);

            auto lst = ResourceManager::getInstance()->lstFileType("data/movies.lst");
            std::string movie = "art/cuts/" + lst->strings()->at(_id);

            auto cfglst = ResourceManager::getInstance()->lstFileType("data/moviecfgs.lst");
            std::string moviecfgfile = "art/cuts/" + cfglst->strings()->at(_id);
            _effects.push_back({0,1, 0, 0, 0, 1});

            if (cfglst->strings()->at(_id)!="reserved.cfg")
            {
                auto& vfs = ResourceManager::getInstance()->vfs();
                auto file = vfs->open(moviecfgfile, VFS::IFile::OpenMode::Read);
                if (!file || !file->isOpened()) {
                    throw Exception("Could not open movie config file");
                }

                std::string content;
                content.resize(file->size());
                file->read(content.data(), file->size());
                vfs->close(file);

                std::istringstream contentStream(content);

                auto inifile = new Ini::Parser(contentStream);
                auto ini = inifile->parse();
                int total_effects = ini->section("info")->propertyInt("total_effects",0);
                auto effect_frames = ini->section("info")->propertyArray("effect_frames");
                for (int i = 0; i < total_effects; i++)
                {
                    unsigned int effect_frame = effect_frames.at(i).intValue();
                    std::string effect_section = effect_frames.at(i).value();
                    int dir = (ini->section(effect_section)->propertyString("fade_type","in") == "in" ? -1 : 1);
                    int steps = ini->section(effect_section)->propertyInt("fade_steps",0);
                    auto colors = ini->section(effect_section)->propertyArray("fade_color");
                    int r = colors[0].intValue()*4;
                    int g = colors[1].intValue()*4;
                    int b = colors[2].intValue()*4;
                    _effects.push_back({effect_frame, dir, r, g, b, steps/15*1000});
                }
            }
            else
            {
                _effects.push_back({1,-1, 0, 0, 0, 1});
            }

            auto sublst = ResourceManager::getInstance()->lstFileType("data/subtitles.lst");
            std::string subfile = "text/english/cuts/" + sublst->strings()->at(_id);

            if (sublst->strings()->at(_id)!="reserved.sve")
            {
                _subs = ResourceManager::getInstance()->sveFileType(subfile);
                if (_subs) {
                    _hasSubs = true;
                }
            }
            addUI("movie", new UI::MvePlayer(ResourceManager::getInstance()->mveFileType(movie)));

            auto font0_ffffffff = ResourceManager::getInstance()->font("font1.aaf");
            auto subLabel = new UI::TextArea("", 0, 320+35);

            subLabel->setFont(font0_ffffffff, {0xFF, 0xFF, 0xFF, 0xFF});
            subLabel->setWidth(640);
            subLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
            addUI("subs",subLabel);

            if (_hasSubs) {
                _nextSubLine = _subs->getSubLine(0);
            } else {
                _nextSubLine = std::pair<int, std::string>(999999, "");
            }
        }

        void Movie::think(const float &deltaTime)
        {
            State::think(deltaTime);

            if (!_active) {
                return;
            }

            unsigned int frame = dynamic_cast<UI::MvePlayer*>(getUI("movie"))->frame();
            if (frame >= _nextSubLine.first) {
                dynamic_cast<UI::TextArea*>(getUI("subs"))->setText(_nextSubLine.second);
                if (_hasSubs) {
                    _nextSubLine = _subs->getSubLine(dynamic_cast<UI::MvePlayer*>(getUI("movie"))->frame());
                }
            }
            if (_effectIndex <_effects.size() && frame>=_effects[_effectIndex].frame) {
                if (_effects[_effectIndex].direction < 0) {
                    Game::Game::getInstance()->renderer()->fadeIn(_effects[_effectIndex].r, _effects[_effectIndex].g, _effects[_effectIndex].b, _effects[_effectIndex].frames, true);
                } else {
                    Game::Game::getInstance()->renderer()->fadeOut(_effects[_effectIndex].r, _effects[_effectIndex].g, _effects[_effectIndex].b, _effects[_effectIndex].frames, true);
                }
                _effectIndex++;
            }

            if (!_started)
            {
                Game::Game::getInstance()->mixer()->playMovieMusic(dynamic_cast<UI::MvePlayer*>(getUI("movie")));
                _started = true;
            }
            if ((dynamic_cast<UI::MvePlayer*>(getUI("movie")))->finished())
            {
                this->onVideoFinished();
            }
        }


        void Movie::handle(Event::Event* event)
        {
            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                if (mouseEvent->name() == "mouseup")
                {
                    this->onVideoFinished();
                }
            }

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                if (keyboardEvent->name() == "keyup")
                {
                    this->onVideoFinished();
                }
            }
        }

        void Movie::onVideoFinished()
        {
            Game::Game::getInstance()->mixer()->stopMusic();

            // without this the location will be absolutely dark if you didn't interrupted movie play
            if (Game::Game::getInstance()->locationState())
            {
                fadeDoneHandler().clear();
                Game::Game::getInstance()->renderer()->fadeIn(255, 255, 255, 500);
            }

            Game::Game::getInstance()->popState();
        }

        void Movie::onStateActivate(Event::State* event) {
            _previousCursor = mouse()->cursor();
            mouse()->setCursor(Cursor::NONE);
        }

        void Movie::onStateDeactivate(Event::State* event) {
            mouse()->setCursor(_previousCursor);
        }
    }
}
