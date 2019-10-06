#include <algorithm>
#include <memory>
#include "../State/State.h"
#include "../Event/State.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../UI/ImageList.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        State::State() : Event::EventTarget(Game::getInstance()->eventDispatcher())
        {
            activateHandler().add([this](Event::State* event) {
                this->onStateActivate(event);
            });
            deactivateHandler().add([this](Event::State* event) {
                this->onStateDeactivate(event);
            });
            keyDownHandler().add([this](Event::Keyboard* event) {
                this->onKeyDown(event);
            });
        }

        State::~State()
        {
        }

        void State::init()
        {
            _initialized = true;
        }

        void State::think()
        {
            for (auto& ui : _ui) {
                ui->think();
            }
        }

        int State::x() const
        {
            return _position.x();
        }

        void State::setX(int x)
        {
            _position.setX(x);
        }

        int State::y() const
        {
            return _position.y();
        }

        void State::setY(int y)
        {
            _position.setY(y);
        }

        const Point& State::position() const
        {
            return _position;
        }

        void State::setPosition(const Point& pos)
        {
            _position = pos;
        }

        bool State::initialized()
        {
            return _initialized;
        }

        bool State::fullscreen() const
        {
            return _fullscreen;
        }

        void State::setFullscreen(bool value)
        {
            _fullscreen = value;
        }

        bool State::modal() const
        {
            return _modal;
        }

        void State::setModal(bool value)
        {
            _modal = value;
        }

        // TODO: change to accept unique_ptr
        UI::Base* State::addUI(UI::Base* ui)
        {
            // Add to UI state position
            ui->setPosition(ui->position() - ui->offset() + position());

            _ui.push_back(std::unique_ptr<UI::Base>(ui));
            return ui;
        }

        UI::Base* State::addUI(const std::string& name, UI::Base* ui)
        {
            addUI(ui);
            _labeledUI.insert(std::pair<std::string, UI::Base*>(name, ui));
            return ui;
        }

        void State::addUI(const std::vector<UI::Base*>& uis)
        {
            for (auto ui : uis) {
                addUI(ui);
            }
        }

        UI::TextArea* State::getTextArea(const std::string& name)
        {
            return dynamic_cast<UI::TextArea*>(getUI(name));
        }

        UI::ImageList* State::getImageList(const std::string& name)
        {
            return dynamic_cast<UI::ImageList*>(getUI(name));
        }

        UI::SmallCounter* State::getSmallCounter(const std::string& name)
        {
            return dynamic_cast<UI::SmallCounter*>(getUI(name));
        }

        UI::Base* State::getUI(const std::string& name)
        {
            if (_labeledUI.find(name) != _labeledUI.end()) {
                return _labeledUI.at(name);
            }
            return nullptr;
        }

        void State::handle(Event::Event* event)
        {
            if (event->handled()) {
                return;
            }
            // TODO: maybe make handle() a template function to get rid of dynamic_casts?
            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event)) {
                if (keyboardEvent->originalType() == Event::Keyboard::Type::KEY_UP) {
                    emitEvent(std::make_unique<Event::Keyboard>(*keyboardEvent), keyUpHandler());
                }
                if (keyboardEvent->originalType() == Event::Keyboard::Type::KEY_DOWN) {
                    emitEvent(std::make_unique<Event::Keyboard>(*keyboardEvent), keyDownHandler());
                }
            }

            for (auto it = _ui.rbegin(); it != _ui.rend(); ++it) {
                if (event->handled()) {
                    return;
                }
                (*it)->handle(event);
            }
        }

        void State::render()
        {
            for (auto& ui : _ui) {
                if (ui->visible()) {
                    ui->render(false);
                }
            }
            _uiToDelete.clear();
        }

        void State::popUI()
        {
            if (_ui.size() == 0) {
                return;
            }
            _uiToDelete.emplace_back(std::move(_ui.back()));
            _ui.pop_back();
        }

        void State::onStateActivate(Event::State* event)
        {
        }

        void State::onStateDeactivate(Event::State* event)
        {
        }

        void State::onKeyDown(Event::Keyboard* event)
        {
        }

        bool State::active()
        {
            return _active;
        }

        void State::setActive(bool value)
        {
            _active = value;
        }

        Event::StateHandler& State::pushHandler()
        {
            return _pushHandler;
        }

        Event::StateHandler& State::popHandler()
        {
            return _popHandler;
        }

        Event::StateHandler& State::activateHandler()
        {
            return _activateHandler;
        }

        Event::StateHandler& State::deactivateHandler()
        {
            return _deactivateHandler;
        }

        Event::StateHandler& State::fadeDoneHandler()
        {
            return _fadeDoneHandler;
        }

        Event::KeyboardHandler& State::keyDownHandler()
        {
            return _keyDownHandler;
        }

        Event::KeyboardHandler& State::keyUpHandler()
        {
            return _keyUpHandler;
        }

        void State::scriptFade(VM::Script *script, bool in)
        {
            fadeDoneHandler().clear();
            fadeDoneHandler().add([this, script](Event::Event* event) {
                fadeDoneHandler().clear();
                script->run();
            });

            if (in) {
                Game::getInstance()->renderer()->fadeIn(0, 0, 0, 1000);
            } else {
                Game::getInstance()->renderer()->fadeOut(0, 0, 0, 1000);
            }
        }
    }
}
