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

    _engineSettings = new EngineSettings();
    auto width = _engineSettings->screenWidth();
    auto height = _engineSettings->screenHeight();

    switch (_engineSettings->renderer())
    {
        case EngineSettings::Renderer::SDL:
            _renderer = new SDLRenderer(width, height);
            break;
        case EngineSettings::Renderer::OPENGL:
            _renderer = new OpenGLRenderer(width, height);
            break;
    }

    Logger::info("GAME") << CrossPlatform::getVersion() << std::endl;
    Logger::info("GAME") << "Opensource Fallout 2 game engine" << std::endl;

    putenv(strdup("SDL_VIDEO_CENTERED=1"));

    _resourceManager = new ResourceManager();

    renderer()->init();

    std::string version = CrossPlatform::getVersion();
    renderer()->setCaption(version.c_str());

    //_mixer = new AudioMixer();
    _mouse = new Mouse();
    _fpsCounter = new FpsCounter(renderer()->width() - 42, 2);

    version += " " + std::to_string(renderer()->width()) + "x" + std::to_string(renderer()->height());
    version += " " + renderer()->name();

    _falltergeistVersion = new TextArea(version, 3, renderer()->height() - 10);
    _mousePosition = new TextArea("", renderer()->width() - 55, 14);
}

Game::~Game()
{
    _instanceFlag = false;
    delete _mouse;
    delete _fpsCounter;
    delete _mousePosition;
    delete _falltergeistVersion;
    delete _mixer;
    delete _resourceManager;
    while (!_states.empty()) popState();
    delete _renderer;
    delete _engineSettings;
}

void Game::pushState(State* state)
{
    _states.push_back(state);
    if (!state->initialized()) state->init();
}

void Game::popState()
{
    if (_states.size() == 0) return;
    _statesForDelete.push_back(_states.back());
    _states.pop_back();
}

void Game::setState(State* state)
{
    while (!_states.empty()) popState();
    pushState(state);
}

void Game::run()
{
    Logger::info("GAME") << "Starting main loop" << std::endl;
    while (!_quit)
    {
        handle();
        think();
        render();
        SDL_Delay(1);
        while (!_statesForDelete.empty())
        {
            delete _statesForDelete.back();
            _statesForDelete.pop_back();
        }
    }
    Logger::info("GAME") << "Stopping main loop" << std::endl;
}

void Game::quit()
{
    _quit = true;
}

void Game::setPlayer(GameDudeObject* player)
{
    _player = player;
}

GameDudeObject* Game::player()
{
    return _player;
}

Mouse* Game::mouse()
{
    return _mouse;
}

LocationState* Game::locationState()
{
    for (auto state : _states)
    {
        auto locationState = dynamic_cast<LocationState*>(state);
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

std::vector<State*>* Game::states()
{
    return &_states;
}

std::vector<State*>* Game::statesForRender()
{
    _statesForRender.clear();
    auto it = _states.end();
    do
    {
        --it;
    }
    while(it != _states.begin() && !(*it)->fullscreen());

    for (; it != _states.end(); ++it)
    {
        if (*it) _statesForRender.push_back(*it);
    }
    return &_statesForRender;
}

std::vector<State*>* Game::statesForThinkAndHandle()
{
    _statesForThinkAndHandle.clear();
    auto it = _states.end();
    do
    {
        --it;
    }
    while(it != _states.begin() && !(*it)->modal() && !(*it)->fullscreen());

    for (; it != _states.end(); ++it)
    {
        if (*it) _statesForThinkAndHandle.push_back(*it);
    }
    return &_statesForThinkAndHandle;
}

Renderer* Game::renderer()
{
    return _renderer;
}

EngineSettings* Game::engineSettings()
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
                    for (auto state : *statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    auto event = std::shared_ptr<MouseEvent>(new MouseEvent("mouseup"));
                    event->setX(_event.button.x);
                    event->setY(_event.button.y);
                    event->setLeftButton(_event.button.button == SDL_BUTTON_LEFT);
                    event->setRightButton(_event.button.button == SDL_BUTTON_RIGHT);
                    for (auto state : *statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    auto event = std::shared_ptr<MouseEvent>(new MouseEvent("mousemove"));
                    event->setX(_event.motion.x);
                    event->setY(_event.motion.y);
                    event->setXOffset(_event.motion.xrel);
                    event->setYOffset(_event.motion.yrel);
                    for (auto state : *statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_KEYDOWN:
                {
                    auto event = std::shared_ptr<KeyboardEvent>(new KeyboardEvent("keydown"));
                    event->setKeyCode(_event.key.keysym.sym);
                    event->setShiftPressed(_event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT));
                    for (auto state : *statesForThinkAndHandle()) state->handle(event);
                    break;
                }
                case SDL_KEYUP:
                {
                    auto event = std::shared_ptr<KeyboardEvent>(new KeyboardEvent("keyup"));
                    event->setKeyCode(_event.key.keysym.sym);
                    event->setShiftPressed(_event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT));
                    for (auto state : *statesForThinkAndHandle()) state->handle(event);

                    if (!event->handled())
                    {
                        if (event->keyCode() == SDLK_F10)
                        {
                            _quit = true;
                        }

                        if (event->keyCode() == SDLK_F11)
                        {
                            Texture* texture = renderer()->screenshot();
                            SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(texture->data(), texture->width(), texture->height(), 32, texture->width()*4, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);                            
                            std::string name = std::to_string(SDL_GetTicks()) +  ".bmp";
                            SDL_SaveBMP(surface, name.c_str());
                            SDL_FreeSurface(surface);                            
                            delete texture;
                            Logger::info("GAME") << "Screenshot saved to " + name << std::endl;

                        }
                    }
                    break;
                }
            }
        }
    }
}

void Game::think()
{
    _fpsCounter->think();
    _mouse->think();

    //Surface::animatedPalette->think();

    _mousePosition->setText(std::to_string(mouse()->x()) + " : " + std::to_string(mouse()->y()));

    for (auto state : *statesForThinkAndHandle())
    {
        state->think();
    }
}

void Game::render()
{
    renderer()->beginFrame();
    for (auto state : *statesForRender())
    {
        state->render();
    }
    _fpsCounter->render();
    _falltergeistVersion->render();
    _mousePosition->render();
    _mouse->render();
    renderer()->endFrame();
}

}
