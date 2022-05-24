#pragma once

#include <list>
#include <memory>
#include "../Format/Map/File.h"
#include "../Game/DudeObject.h"
#include "../Game/Object.h"
#include "../Game/Timer.h"
#include "../Game/LocationState/ScrollHandler.h"
#include "../Graphics/Lightmap.h"
#include "../Input/Mouse.h"
#include "../State/State.h"
#include "../UI/ImageButton.h"
#include "../UI/ScrollHitBox.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace Audio
    {
        class Mixer;
    }
    namespace Format
    {
        namespace Map
        {
            class Object;
        }
    }
    namespace Game
    {
        class DudeObject;
        class Location;
        class Object;
        class SpatialObject;
        class Time;
    }
    namespace UI
    {
        class Animation;
        class Image;
        class PlayerPanel;
        class Tile;
        class TileMap;
    }
    namespace VM
    {
        class Script;
        class StackValue;
    }
    class Hexagon;
    class HexagonGrid;
    class LocationCamera;
    class Settings;

    namespace State
    {
        /**
         * Location state works whenever player is on some map.
         * This state holds pointers to all object on current map, hexagon grid and other map-specific information.
         *
         * pushed: when player starts new game or loads new game
         * popped: when player closes the game, exits to main menu or loads the game
         */
        class Location final : public State
        {
            public:
                /**
                 * Current player action. What user is doing at location: using skill, attacking, pointing on smth, etc...
                 */
                enum class PlayerAction {
                    DEFAULT,
                    MOVE,
                    USE_SKILL
                };

                Location(
                    std::shared_ptr<Game::DudeObject> player,
                    std::shared_ptr<Input::Mouse> mouse,
                    std::shared_ptr<Settings> settings,
                    std::shared_ptr<Graphics::Renderer> renderer,
                    std::shared_ptr<Audio::Mixer> audioMixer,
                    std::shared_ptr<Game::Time> gameTime,
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<ILogger> logger
                );

                ~Location() override = default;

                void init() override;

                void think(const float &deltaTime) override;

                void handle(Event::Event* event) override;

                void render() override;

                void handleByGameObjects(Event::Mouse* event);

                HexagonGrid* hexagonGrid();

                LocationCamera* camera();

                std::shared_ptr<Game::Location> location();

                void setLocation(std::shared_ptr<Game::Location> location);

                unsigned int elevation() const;

                void setElevation(unsigned int elevation);

                void setMVAR(unsigned int number, int value);

                int MVAR(unsigned int number);

                std::map<std::string, VM::StackValue>* EVARS();

                void moveObjectToHexagon(Game::Object *object, Hexagon *hexagon, bool update = true);

                void removeObjectFromMap(Game::Object *object);

                void destroyObject(Game::Object* object);

                void centerCameraAtHexagon(Hexagon* hexagon);

                void centerCameraAtHexagon(int tileNum);

                void handleAction(Game::Object* object, Input::Mouse::Icon action);

                void displayMessage(const std::string& message);

                void addTimerEvent(Game::Object* obj, int ticks, int fixedParam = 0);

                void removeTimerEvent(Game::Object* obj);

                void removeTimerEvent(Game::Object* obj, int fixedParam);

                void onBackgroundClick(Event::Mouse* event);

                void onObjectMouseEvent(Event::Mouse* event, Game::Object* object);

                void onObjectHover(Event::Mouse* event, Game::Object* object);

                void onKeyDown(Event::Keyboard* event) override;

                void onMouseUp(Event::Mouse* event);

                void onMouseDown(Event::Mouse* event);

                void onMouseMove(Event::Mouse* event);

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

                unsigned int lightLevel();

                void setLightLevel(unsigned int level);

                unsigned int currentMapIndex();

                UI::PlayerPanel* playerPanel();

                void initLight();

                Game::Object* addObject(unsigned int PID, unsigned int position, unsigned int elevation);

                SKILL skillInUse() const;

                void useSkill(SKILL skill);

                PlayerAction playerAction() const;

            private:
                struct TimerEvent
                {
                    Game::Object* object;
                    Game::Timer timer;
                    int fixedParam;
                };

                std::vector<Input::Mouse::Icon> _getCursorIconsForObject(Game::Object* object);

                void _initializePlayerTestAppareance(std::shared_ptr<Game::DudeObject> player) const;

                void _initializeLightmap();

                void _loadAmbient(const std::string &name);

                void _renderCursor() const;

                void _renderObjects() const;

                void _renderObjectsText() const;

                void _renderCursorOutline() const;

                void _renderTestingOutline() const;

                void _thinkObjects(const float &deltaTime) const;

                void _performScrolling(const float &deltaTime);

                void _firstLocationEnter(const float &deltaTime) const;

                void _processTimers(const float &deltaTime);

                bool _movePlayerToObject(Game::Object *object);

                void _setDefaultPlayerAction();

                void _setMovePlayerAction();

                void _togglePlayerAction();

                Game::Object* _getGameObjectUnderCursor();

                std::shared_ptr<Game::DudeObject> _player;

                std::shared_ptr<Settings> _settings;

                std::shared_ptr<Graphics::Renderer> _renderer;

                std::shared_ptr<Audio::Mixer> _audioMixer;

                std::shared_ptr<Game::Time> _gameTime;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::shared_ptr<ILogger> _logger;

                static const int KEYBOARD_SCROLL_STEP;

                static const int DROPDOWN_DELAY;

                // Timers
                Game::Timer _locationScriptTimer;

                Game::Timer _actionCursorTimer;

                Game::Timer _ambientSfxTimer;

                // for VM opcode add_timer_event
                std::list<TimerEvent> _timerEvents;

                // TODO: move to Game::Location class?
                std::map<std::string, unsigned char> _ambientSfx;

                std::unique_ptr<HexagonGrid> _hexagonGrid;

                std::unique_ptr<LocationCamera> _camera;

                std::map<std::string, VM::StackValue> _EVARS;

                std::shared_ptr<Falltergeist::Game::Location> _location;

                unsigned int _elevation = 0;

                bool _locationEnter = true;

                unsigned int _currentMap = 0;

                unsigned int _lastClickedTile = 0;

                Game::Object* _objectUnderCursor = nullptr;

                Game::Object* _actionCursorLastObject = nullptr;

                bool _actionCursorButtonPressed = false;

                UI::PlayerPanel* _playerPanel;
                UI::ScrollHitBox* _scrollHitBox;
                std::unique_ptr<Game::LocationState::ScrollHandler> _scrollHandler;

                SKILL _skillInUse = SKILL::NONE;

                std::list<std::shared_ptr<Game::Object>> _objects;

                std::list<std::shared_ptr<Game::Object>> _flatObjects;

                std::unique_ptr<UI::TextArea> _hexagonInfo;

                Event::MouseHandler _mouseDownHandler, _mouseUpHandler, _mouseMoveHandler;

                unsigned int _lightLevel = 0x10000;

                Falltergeist::Graphics::Lightmap* _lightmap;

                std::vector<Game::SpatialObject*> _spatials;

                PlayerAction _playerAction = PlayerAction::DEFAULT;
        };
    }
}
