#include <algorithm>
#include <sstream>
#include <ctime>
#include <memory>
#include <SDL_image.h>
#include "../Audio/Mixer.h"
#include "../CrossPlatform.h"
#include "../Event/Dispatcher.h"
#include "../Event/State.h"
#include "../Exception.h"
#include "../Format/Gam/File.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/Time.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/State.h"
#include "../State/Location.h"
#include "../UI/FpsCounter.h"
#include "../UI/TextArea.h"

namespace
{
    Falltergeist::Graphics::RendererConfig cfg_from_settings(const Falltergeist::Settings& settings)
    {
        Falltergeist::Graphics::RendererConfig cfg{
                .width = settings.screenWidth(),
                .height = settings.screenHeight(),
                .fullscreen = settings.fullscreen(),
                .alwaysOnTop = settings.alwaysOnTop(),
        };
        if (settings.screenX() >= 0) {
            cfg.x = settings.screenX();
        }
        if (settings.screenY() >= 0) {
            cfg.y = settings.screenY();
        }
        return cfg;
    }
}

namespace Falltergeist
{
    namespace Game
    {
        using namespace Base;

        Game* getInstance()
        {
            return ::Falltergeist::Game::Game::getInstance();
        }

        Game::Game()
        {
        }

        Game* Game::getInstance()
        {
            return Base::Singleton<Game>::get();
        }

        void Game::init(std::unique_ptr<Settings> settings)
        {
            if (_initialized) {
                return;
            }
            _initialized = true;

            _settings = std::move(settings);

            _eventDispatcher = std::make_unique<Event::Dispatcher>();

            _renderer = std::make_shared<Graphics::Renderer>(cfg_from_settings(*_settings));

            Logger::info("GAME") << CrossPlatform::getVersion() << std::endl;
            Logger::info("GAME") << "Opensource Fallout 2 game engine" << std::endl;

            SDL_setenv("SDL_VIDEO_CENTERED", "1", 1);

            // Force ResourceManager to initialize instance.
            (void)ResourceManager::getInstance();

            renderer()->init();

            std::string version = CrossPlatform::getVersion();
            renderer()->setCaption(version.c_str());

            _mixer = std::make_shared<Audio::Mixer>();
            _mixer->setMusicVolume(_settings->musicVolume());
            _mouse = std::make_shared<Input::Mouse>(uiResourceManager);
            _fpsCounter = std::make_unique<UI::FpsCounter>(Point(renderer()->width() - 42, 2));
            _fpsCounter->setWidth(42);
            _fpsCounter->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

            version += " " + to_string(renderer()->size());

            _falltergeistVersion = std::make_unique<UI::TextArea>(version, 3, renderer()->height() - 10);
            _mousePosition = std::make_unique<UI::TextArea>("", renderer()->width() - 55, 14);
            _mousePosition->setWidth(55);
            _mousePosition->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
            _animatedPalette = std::make_unique<Graphics::AnimatedPalette>();
            _gameTime = std::make_shared<Time>();
            _currentTime = std::make_unique<UI::TextArea>("", renderer()->size() - Point(150, 10));
            _currentTime->setWidth(150);
            _currentTime->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);

            IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

            srand(static_cast<unsigned>(time(0))); /// randomization

            atexit(SDL_Quit);
        }

        Game::~Game()
        {
            shutdown();
        }

        void Game::shutdown()
        {
            _mixer.reset();
            ResourceManager::getInstance()->shutdown();
            while (!_states.empty()) {
                popState();
            }
            _settings.reset();
        }

        void Game::pushState(State::State* state)
        {
            _states.push_back(std::unique_ptr<State::State>(state));
            if (!state->initialized()) {
                state->init();
            }
            state->emitEvent(std::make_unique<Event::State>("push"), state->pushHandler());
            state->setActive(true);
            state->emitEvent(std::make_unique<Event::State>("activate"), state->activateHandler());
        }

        void Game::popState(bool doDelete)
        {
            if (_states.empty()) {
                return;
            }

            State::State* state = _states.back().get();
            if (doDelete) {
                _statesForDelete.emplace_back(std::move(_states.back()));
            } else {
                _states.back().release();
            }
            _states.pop_back();
            state->setActive(false);
            state->emitEvent(std::make_unique<Event::State>("deactivate"), state->deactivateHandler());
            state->emitEvent(std::make_unique<Event::State>("pop"), state->popHandler());
        }

        void Game::setState(State::State* state)
        {
            while (!_states.empty()) {
                popState();
            }
            pushState(state);
        }

        void Game::run()
        {
            Logger::info("GAME") << "Starting main loop" << std::endl;
            _frame = 0;

            uint32_t FPS = 60;
            uint32_t frameDelay = 1000 / FPS;

            uint32_t frameStart = 0;
            uint32_t frameTime = 0;
            while (!_quit) {
                frameStart = SDL_GetTicks();

                handle();
                think(frameTime);
                render();
                _statesForDelete.clear();
                _frame++;

                frameTime = SDL_GetTicks() - frameStart;
                if (frameDelay > frameTime) {
                    SDL_Delay(frameDelay - frameTime);
                    frameTime += (frameDelay - frameTime);
                }
            }
            Logger::info("GAME") << "Stopping main loop" << std::endl;
        }

        void Game::quit()
        {
            _quit = true;
        }

        void Game::setPlayer(std::shared_ptr<DudeObject> player)
        {
            _player = std::move(player);
        }

        std::shared_ptr<DudeObject> Game::player() const
        {
            return _player;
        }

        std::shared_ptr<Input::Mouse> Game::mouse() const
        {
            return _mouse;
        }

        State::Location* Game::locationState()
        {
            for (auto& state : _states) {
                auto location = dynamic_cast<State::Location*>(state.get());
                if (location) {
                    return location;
                }
            }
            return nullptr;
        }

        void Game::setGVAR(unsigned int number, int value)
        {
            _initGVARS();
            if (number >= _GVARS.size()) {
                throw Exception("Game::setGVAR(num, value) - num out of range: " + std::to_string(number));
            }
            _GVARS.at(number) = value;
        }

        int Game::GVAR(unsigned int number)
        {
            _initGVARS();
            if (number >= _GVARS.size()) {
                throw Exception("Game::GVAR(num) - num out of range: " + std::to_string(number));
            }
            return _GVARS.at(number);
        }

        void Game::_initGVARS()
        {
            if (!_GVARS.empty()) {
                return;
            }
            auto gam = ResourceManager::getInstance()->gamFileType("data/vault13.gam");
            for (auto gvar : *gam->GVARS()) {
                _GVARS.push_back(gvar.second);
            }
        }

        State::State* Game::topState(unsigned offset) const
        {
            return (_states.rbegin() + offset)->get();
        }

        std::vector<State::State*> Game::_getVisibleStates()
        {
            std::vector<State::State*> subset;
            if (_states.empty()) {
                return subset;
            }
            // we must render all states from last fullscreen state to the top of stack
            auto it = _states.end();
            do {
                --it;
            } while (it != _states.begin() && !(*it)->fullscreen());

            for (; it != _states.end(); ++it) {
                subset.push_back((*it).get());
            }
            return subset;
        }

        std::vector<State::State*> Game::_getActiveStates()
        {
            // we must handle all states from top to bottom of stack
            std::vector<State::State*> subset;

            auto it = _states.rbegin();
            // active states
            for (; it != _states.rend(); ++it) {
                auto state = it->get();
                if (!state->active()) {
                    state->emitEvent(std::make_unique<Event::State>("activate"), state->activateHandler());
                    state->setActive(true);
                }
                subset.push_back(state);
                if (state->modal() || state->fullscreen()) {
                    ++it;
                    break;
                }
            }
            // not active states
            for (; it != _states.rend(); ++it) {
                auto state = it->get();
                if (state->active()) {
                    state->emitEvent(std::make_unique<Event::State>("deactivate"), state->deactivateHandler());
                    state->setActive(false);
                }
            }
            return subset;
        }

        std::shared_ptr<Graphics::Renderer> Game::renderer() const
        {
            return _renderer;
        }

        std::shared_ptr<Settings> Game::settings() const
        {
            return _settings;
        }

        // TODO: probably need to move this to factory class
        std::unique_ptr<Event::Event> Game::_createEventFromSDL(const SDL_Event& sdlEvent)
        {
            using Mouse = Event::Mouse;
            using Keyboard = Event::Keyboard;
            switch (sdlEvent.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    SDL_Keymod mods = SDL_GetModState();
                    auto mouseEvent = std::make_unique<Mouse>((sdlEvent.type == SDL_MOUSEBUTTONDOWN) ? Mouse::Type::BUTTON_DOWN : Mouse::Type::BUTTON_UP);
                    mouseEvent->setPosition({sdlEvent.button.x, sdlEvent.button.y});
                    switch (sdlEvent.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            mouseEvent->setButton(Mouse::Button::LEFT);
                            break;
                        case SDL_BUTTON_RIGHT:
                            mouseEvent->setButton(Mouse::Button::RIGHT);
                            break;
                        case SDL_BUTTON_MIDDLE:
                            mouseEvent->setButton(Mouse::Button::MIDDLE);
                            break;
                        case SDL_BUTTON_X1:
                            mouseEvent->setButton(Mouse::Button::X1);
                            break;
                        case SDL_BUTTON_X2:
                            mouseEvent->setButton(Mouse::Button::X2);
                            break;
                    }
                    mouseEvent->setShiftPressed(mods & KMOD_SHIFT);
                    mouseEvent->setControlPressed(mods & KMOD_CTRL);
                    mouseEvent->setAltPressed(mods & KMOD_ALT);
                    return std::move(mouseEvent);
                }
                case SDL_MOUSEMOTION:
                {
                    auto mouseEvent = std::make_unique<Event::Mouse>(Mouse::Type::MOVE);
                    mouseEvent->setPosition({sdlEvent.motion.x, sdlEvent.motion.y});
                    mouseEvent->setOffset({sdlEvent.motion.xrel,sdlEvent.motion.yrel});
                    return std::move(mouseEvent);
                }
                case SDL_KEYDOWN:
                {
                    auto keyboardEvent = std::make_unique<Event::Keyboard>(Keyboard::Type::KEY_DOWN);
                    keyboardEvent->setKeyCode(sdlEvent.key.keysym.sym);
                    keyboardEvent->setAltPressed(sdlEvent.key.keysym.mod & KMOD_ALT);
                    keyboardEvent->setShiftPressed(sdlEvent.key.keysym.mod & KMOD_SHIFT);
                    keyboardEvent->setControlPressed(sdlEvent.key.keysym.mod & KMOD_CTRL);
                    return std::move(keyboardEvent);
                }
                case SDL_KEYUP:
                {
                    auto keyboardEvent = std::make_unique<Event::Keyboard>(Keyboard::Type::KEY_UP);
                    keyboardEvent->setKeyCode(sdlEvent.key.keysym.sym);
                    keyboardEvent->setAltPressed(sdlEvent.key.keysym.mod & KMOD_ALT);
                    keyboardEvent->setShiftPressed(sdlEvent.key.keysym.mod & KMOD_SHIFT);
                    keyboardEvent->setControlPressed(sdlEvent.key.keysym.mod & KMOD_CTRL);;

                    // TODO: maybe we should make Game an EventTarget too?
                    if (keyboardEvent->keyCode() == SDLK_F12)
                    {
                        renderer()->screenshot();
                    }
                    return std::move(keyboardEvent);
                }
            }
            return std::unique_ptr<Event::Event>();
        }

        void Game::handle()
        {
            if (_renderer->fading()) {
                return;
            }

            while (SDL_PollEvent(&_event))
            {
                if (_event.type == SDL_QUIT) {
                    _quit = true;
                } else {
                    auto event = _createEventFromSDL(_event);
                    if (event) {
                        for (auto state : _getActiveStates()) state->handle(event.get());
                    }
                }
                // process events generate during handle()
                _eventDispatcher->processScheduledEvents();
            }
        }

        void Game::think(const float &deltaTime)
        {
            _fpsCounter->think(deltaTime);
            _mouse->think(deltaTime);

            _animatedPalette->think(deltaTime);

            *_mousePosition = "";
            *_mousePosition << mouse()->position().x() << " : " << mouse()->position().y();

            *_currentTime = "";
            *_currentTime << _gameTime->year()  << "-" << _gameTime->month()   << "-" << _gameTime->day() << " "
                          << _gameTime->hours() << ":" << _gameTime->minutes() << ":" << _gameTime->seconds() << " " << _gameTime->ticks();

            // TODO get rid of time in Renderer. It should know nothing about time
            _renderer->think(deltaTime);

            if (_renderer->fading()) {
                return;
            }

            for (auto state : _getActiveStates()) {
                state->think(deltaTime);
            }
            // process custom events
            _eventDispatcher->processScheduledEvents();
        }

        void Game::render()
        {
            renderer()->beginFrame();

            for (auto state : _getVisibleStates()) {
                state->render();
            }

            if (settings()->displayFps()) {
                _fpsCounter->render();
            }

            _falltergeistVersion->render();

            if (settings()->displayMousePosition()) {
                _mousePosition->render();
            }

            _currentTime->render();
            // hexagon is rendered in location after floor
            if (_mouse->state() != Input::Mouse::Cursor::HEXAGON_RED) {
                _mouse->render();
            }
            renderer()->endFrame();
        }

        Graphics::AnimatedPalette* Game::animatedPalette()
        {
            return _animatedPalette.get();
        }

        std::shared_ptr<Time> Game::gameTime() const
        {
            return _gameTime;
        }

        std::shared_ptr<Audio::Mixer> Game::mixer() const
        {
            return _mixer;
        }

        Event::Dispatcher* Game::eventDispatcher()
        {
            return _eventDispatcher.get();
        }

        unsigned int Game::frame() const
        {
            return _frame;
        }

        void Game::setUIResourceManager(std::shared_ptr<UI::IResourceManager> uiResourceManager)
        {
            this->uiResourceManager = uiResourceManager;
        }
    }
}
