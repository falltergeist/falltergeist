#include <sstream>
#include "../State/Credits.h"
#include "../CrossPlatform.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Event/State.h"
#include "../Font.h"
#include "../Game/Game.h"
#include "../Graphics/Color.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../UI/TextArea.h"
#include "../Exception.h"

namespace Falltergeist
{
    namespace State
    {
        Credits::Credits(std::shared_ptr<Input::Mouse> mouse) : State(mouse) {
        }

        Credits::~Credits()
        {
            if (_linePositions != nullptr) {
                delete[] _linePositions;
                _linePositions = nullptr;
            }
        }

        void Credits::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setModal(true);
            setFullscreen(true);

            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::NONE);
            auto renderer = Game::Game::getInstance()->renderer();
            setPosition(Graphics::Point((renderer->size().width() - 640) / 2, renderer->size().height()));

            auto& vfs = ResourceManager::getInstance()->vfs();
            auto file = vfs->open("text/english/credits.txt", VFS::IFile::OpenMode::Read);
            if (!file || !file->isOpened()) {
                throw Exception("Could not open credits file");
            }

            std::string content;
            content.resize(file->size());
            file->read(content.data(), file->size());
            vfs->close(file);

            std::istringstream contentStream(content);

            auto font_default = ResourceManager::getInstance()->font("font4.aaf");
            Graphics::Color default_color = {0x90, 0x78, 0x24, 0xFF};
            auto font_at = ResourceManager::getInstance()->font("font3.aaf");
            Graphics::Color at_color = { 0x70, 0x60, 0x50, 0xFF};
            auto font_hash = ResourceManager::getInstance()->font("font4.aaf");
            Graphics::Color hash_color = { 0x8c, 0x8c, 0x84, 0xFF};

            int y = 0;
            std::string line;
            while (std::getline(contentStream, line))
            {
                Graphics::Font* cur_font = font_default;
                Graphics::Color cur_color = default_color;
                int additionalGap = 0;
                if (line.find('\r') != std::string::npos) {
                    line.erase(line.find('\r'));
                }
                if (line[0] == '#') {
                    line.erase(line.begin());
                    cur_font = font_hash;
                    cur_color = hash_color;
                } else if (line[0] == '@') {
                    line.erase(line.begin());
                    cur_font = font_at;
                    cur_color = at_color;
                    additionalGap = 6;
                } else if (line.empty()) {
                    line = "    ";
                }

                auto tx = new UI::TextArea(line, 0, y);
                tx->setFont(cur_font, cur_color);
                tx->setSize({640, 0});
                tx->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
                addUI(tx);
                _lines.push_back(tx);
                y += tx->textSize().height() + cur_font->verticalGap() + additionalGap;
            }

            _linePositions = new int[_lines.size()];

            for (size_t i = 0; i < _lines.size(); i++) {
                _linePositions[i] = _lines.at(i)->position().y();
            }
        }

        void Credits::think(const float &deltaTime)
        {
            State::think(deltaTime);

            auto scrollingSpeed = 1.0f / 33.0f;

            _timePassed += deltaTime;

            long int _lastY = 0;
            for (size_t i = 0; i < _lines.size(); i++) {
                auto ui = _lines.at(i);
                int yPosition = _linePositions[i] - static_cast<int>(_timePassed * scrollingSpeed);
                ui->setY(yPosition);
                _lastY = ui->position().y();
            }

            if (_lastY < -30) {
                this->onCreditsFinished();
            }
        }

        void Credits::handle(Event::Event* event)
        {
            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                if (mouseEvent->name() == "mouseup")
                {
                    this->onCreditsFinished();
                }
            }

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                if (keyboardEvent->name() == "keyup")
                {
                    this->onCreditsFinished();
                }
            }
        }

        void Credits::onCreditsFinished()
        {
            fadeDoneHandler().clear();
            fadeDoneHandler().add([this](Event::Event* event){ this->onCreditsFadeDone(dynamic_cast<Event::State*>(event)); });
            Game::Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
        }

        void Credits::onCreditsFadeDone(Event::State* event)
        {
            fadeDoneHandler().clear();
            Game::Game::getInstance()->mouse()->popState();
            Game::Game::getInstance()->popState();
        }

        void Credits::onStateActivate(Event::State* event)
        {
            Game::Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
        }
    }
}
