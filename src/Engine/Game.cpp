/*
 * Copyright 2012-2014 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes
#include <sstream>
#include <string>

// Falltergeist includes
#include "../Engine/AnimatedPalette.h"
#include "../Engine/AudioMixer.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Event/Event.h"
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/OpenGLRenderer.h"
#include "../Engine/Graphics/SDLRenderer.h"
#include "../Engine/IniFile.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/Logger.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Settings.h"
#include "../Engine/State.h"
#include "../Engine/UI.h"
#include "../Game/GameDudeObject.h"
#include "../States/LocationState.h"
#include "../UI/FpsCounter.h"
#include "../UI/TextArea.h"

// Third patry includes

namespace Falltergeist
{

bool Game::_instanceFlag = false;
Game* Game::_instance = NULL;

Game* Game::getInstance()
{
    if(!_instanceFlag)
     {
         _instance = new Game();
         _instanceFlag = true;
         _instance->_initialize();
         return _instance;
     }
     else
     {
         return _instance;
     }
}

void Game::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    _engineSettings = std::shared_ptr<EngineSettings>(new EngineSettings());
    auto width = _engineSettings->screenWidth();
    auto height = _engineSettings->screenHeight();

    switch (_engineSettings->renderer())
    {
        case EngineSettings::Renderer::SDL:
            _renderer = std::shared_ptr<SDLRenderer>(new SDLRenderer(width, height));
            break;
        case EngineSettings::Renderer::OPENGL:
            _renderer = std::shared_ptr<OpenGLRenderer>(new OpenGLRenderer(width, height));
            break;
    }

    Logger::info("GAME") << CrossPlatform::getVersion() << std::endl;
    Logger::info("GAME") << "Opensource Fallout 2 game engine" << std::endl;

    putenv(strdup("SDL_VIDEO_CENTERED=1"));

    _resourceManager = std::shared_ptr<ResourceManager>(new ResourceManager());

    renderer()->init();

    std::string version = CrossPlatform::getVersion();
    renderer()->setCaption(version.c_str());

    //_mixer = new AudioMixer();
    _mouse = std::shared_ptr<Mouse>(new Mouse());
    _fpsCounter = std::shared_ptr<FpsCounter>(new FpsCounter(renderer()->width() - 42, 2));

    version += " " + std::to_string(renderer()->width()) + "x" + std::to_string(renderer()->height());
    version += " " + renderer()->name();

    _falltergeistVersion = std::shared_ptr<TextArea>(new TextArea(version, 3, renderer()->height() - 10));
    _mousePosition = std::shared_ptr<TextArea>(new TextArea("", renderer()->width() - 55, 14));
}

Game::~Game()
{
    _instanceFlag = false;
}

void Game::pushState(std::shared_ptr<State> state)
{
    _states.push_back(state);
    if (!state->initialized()) state->init();
}

void Game::popState()
{
    _states.pop_back();
}

void Game::setState(std::shared_ptr<State> state)
{
    _states.clear();
    pushState(state);
}

void Game::run()
{
    Logger::info("GAME") << "Starting main loop" << std::endl;
    while (!_quit)
    {
        handle();

        // thinking
        _fpsCounter->think();
        _mouse->think();

        //Surface::animatedPalette->think();

        _mousePosition->setText(std::to_string(mouse()->x()) + " : " + std::to_string(mouse()->y()));

        for (auto state : statesForThinkAndHandle())
        {
            state->think();
        }

        renderer()->beginFrame();
        renderer()->endFrame();
        SDL_Delay(1);
    }

    Logger::info("GAME") << "Stopping main loop" << std::endl;
}

std::shared_ptr<ResourceManager> Game::resourceManager()
{
    return _resourceManager;
}

void Game::quit()
{
    _quit = true;
}

void Game::setPlayer(std::shared_ptr<GameDudeObject> player)
{
    _player = player;
}

std::shared_ptr<GameDudeObject> Game::player()
{
    return _player;
}

std::shared_ptr<Mouse> Game::mouse()
{
    return _mouse;
}

std::shared_ptr<LocationState> Game::locationState()
{
    for (auto state : _states)
    {
        auto locationState = std::dynamic_pointer_cast<LocationState>(state);
        if (locationState)
        {
            return locationState;
        }
    }
    return 0;
}

void Game::setGVAR(unsigned int number, int value)
{
    _initGVARS();
    if (number >= _GVARS.size())
    {
        throw Exception("Game::setGVAR(num, value) - num out of range: " + std::to_string(number));
    }
    _GVARS.at(number) = value;
}

int Game::GVAR(unsigned int number)
{
    _initGVARS();
    if (number >= _GVARS.size())
    {
        throw Exception("Game::GVAR(num) - num out of range: " + std::to_string(number));
    }
    return _GVARS.at(number);
}

void Game::_initGVARS()
{
    if (_GVARS.size() > 0) return;
    auto gam = ResourceManager::gamFileType("data/vault13.gam");
    for (auto gvar : *gam->GVARS())
    {
        _GVARS.push_back(gvar.second);
    }
}

std::vector<std::shared_ptr<State>>* Game::states()
{
    return &_states;
}

std::vector<std::shared_ptr<State>> Game::statesForRender()
{
    std::vector<std::shared_ptr<State>> states;
    auto it = _states.end();
    do
    {
        --it;
    }
    while(it != _states.begin() && !(*it)->fullscreen());

    for (; it != _states.end(); ++it)
    {
        if (*it) states.push_back(*it);
    }
    return states;
}

std::vector<std::shared_ptr<State>> Game::statesForThinkAndHandle()
{
    std::vector<std::shared_ptr<State>> states;
    auto it = _states.end();
    do
    {
        --it;
    }
    while(it != _states.begin() && !(*it)->modal() && !(*it)->fullscreen());

    for (; it != _states.end(); ++it)
    {
        if (*it) states.push_back(*it);
    }
    return states;
}

std::vector<std::shared_ptr<UI>>* Game::ui()
{
    _ui.clear();

    for (auto state : statesForRender())
    {
        for (auto ui : *state->ui())
        {
            if (ui->visible())
            {
                _ui.push_back(ui);
            }
        }
    }

    _ui.push_back(_fpsCounter);
    _ui.push_back(_falltergeistVersion);
    _ui.push_back(_mousePosition);

    // Render mouse
    if (mouse()->visible() && mouse()->ui())
    {
        _ui.push_back(mouse()->ui());
    }

    return &_ui;
}

std::shared_ptr<Renderer> Game::renderer()
{
    return _renderer;
}

std::shared_ptr<EngineSettings> Game::engineSettings()
{
    return _engineSettings;
}

void Game::handle()
{
    while(SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            _quit = true;
        }
        else
        {
            switch (_event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                {
                    auto event = std::shared_ptr<MouseEvent>(new MouseEvent("mousedown"));
                    event->setX(_event.button.x);
                    event->setY(_event.button.y);
                    event->setLeftButton(_event.button.button == SDL_BUTTON_LEFT);
                    event->setRightButton(_event.button.button == SDL_BUTTON_RIGHT);
                    for (auto state : statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    auto event = std::shared_ptr<MouseEvent>(new MouseEvent("mouseup"));
                    event->setX(_event.button.x);
                    event->setY(_event.button.y);
                    event->setLeftButton(_event.button.button == SDL_BUTTON_LEFT);
                    event->setRightButton(_event.button.button == SDL_BUTTON_RIGHT);
                    for (auto state : statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    auto event = std::shared_ptr<MouseEvent>(new MouseEvent("mousemove"));
                    event->setX(_event.motion.x);
                    event->setY(_event.motion.y);
                    event->setXOffset(_event.motion.xrel);
                    event->setYOffset(_event.motion.yrel);
                    for (auto state : statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_KEYDOWN:
                {
                    auto event = std::shared_ptr<KeyboardEvent>(new KeyboardEvent("keydown"));
                    event->setKeyCode(_event.key.keysym.sym);
                    event->setShiftPressed(_event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT));
                    for (auto state : statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_KEYUP:
                {
                    auto event = std::shared_ptr<KeyboardEvent>(new KeyboardEvent("keyup"));
                    event->setKeyCode(_event.key.keysym.sym);
                    event->setShiftPressed(_event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT));
                    for (auto state : statesForThinkAndHandle()) state->handle(event);

                    if (!event->handled())
                    {
                        if (event->keyCode() == SDLK_F10)
                        {
                            _quit = true;
                        }

                        if (event->keyCode() == SDLK_F11)
                        {
                            std::shared_ptr<Texture> texture = renderer()->screenshot();
                            SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(texture->data(), texture->width(), texture->height(), 32, texture->width()*4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
                            std::string name = std::to_string(SDL_GetTicks()) +  ".bmp";
                            SDL_SaveBMP(surface, name.c_str());
                            SDL_FreeSurface(surface);
                            Logger::info("GAME") << "Screenshot saved to " + name << std::endl;

                        }
                    }
                    break;
                }
            }
        }
    }

}

}
