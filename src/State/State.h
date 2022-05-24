#pragma once

#include <map>
#include <memory>
#include <vector>
#include "../Event/EventTarget.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Graphics/Point.h"
#include "../Input/Mouse.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Event
    {
        class Event;
        class State;
    }
    namespace Game
    {
        class Game;
    }
    namespace UI
    {
        class ImageList;
        class SmallCounter;
        class TextArea;
        class Base;
    }
    namespace State
    {
        class State : public Event::EventTarget
        {
            public:
                State(std::shared_ptr<Input::Mouse> mouse);

                State(const State&) = delete;

                State& operator=(const State&) = delete;

                virtual ~State() = default;

                template <class TUi, class ...TCtorArgs>
                TUi* makeUI(TCtorArgs&&... args)
                {
                    TUi* ptr = new TUi(std::forward<TCtorArgs>(args)...);
                    _ui.emplace_back(ptr);
                    return ptr;
                }

                UI::Base* addUI(UI::Base* ui);

                UI::Base* addUI(const std::string& name, UI::Base* ui);

                void addUI(const std::vector<UI::Base*>& uis);

                void popUI();

                UI::Base* getUI(const std::string& name);

                UI::TextArea* getTextArea(const std::string& name);

                UI::ImageList* getImageList(const std::string& name);

                UI::SmallCounter* getSmallCounter(const std::string& name);

                // @todo: remove getters/setters for x, y?
                virtual int x() const;

                virtual void setX(int x);

                virtual int y() const;

                virtual void setY(int y);

                virtual const Graphics::Point& position() const;

                virtual void setPosition(const Graphics::Point& pos);

                virtual bool fullscreen() const;

                virtual void setFullscreen(bool value);

                virtual bool modal() const;

                virtual void setModal(bool value);

                virtual bool active();

                virtual void setActive(bool value);

                virtual bool initialized();

                virtual void init();

                /**
                 * @brief Handle all OS events (Mouse, Keyboard, etc.) by this state.
                 * Used in Event Capturing process.
                 * This method is called first in the main loop (before think() and render()).
                 */
                virtual void handle(Event::Event* event);
                /**
                 * @brief Process all real-time logic of this state.
                 * This method is called after handle() but before render() in the main loop.
                 */
                virtual void think(const float &deltaTime);
                /**
                 * @brief Renders all visible objects of this state on screen.
                 * This method is called last in the main loop (after handle() and think()).
                 */
                virtual void render();

                virtual void onStateActivate(Event::State* event);

                virtual void onStateDeactivate(Event::State* event);

                virtual void onKeyDown(Event::Keyboard* event);

                /**
                 * Invoked when state becomes active to receive events (when first pushed and after other modal states are removed from "above").
                 */
                Event::StateHandler& activateHandler();
                /**
                 * Invoked when state becomes inactive and won't receive any more events (when popped and also when other modal state is pushed on top of it).
                 */
                Event::StateHandler& deactivateHandler();
                /**
                 * Invoked when state is pushed to the stack, right before the first "activate".
                 */
                Event::StateHandler& pushHandler();
                /**
                 * Invoked when state is popped from the stack, right after last "deactivate".
                 */
                Event::StateHandler& popHandler();
                /**
                 * Invoked when Renderer has finished fadein/fadeout process.
                 */
                Event::StateHandler& fadeDoneHandler();

                Event::KeyboardHandler& keyDownHandler();

                Event::KeyboardHandler& keyUpHandler();

                void scriptFade(VM::Script* script, bool in);


            protected:
                std::vector<std::unique_ptr<UI::Base>> _ui;

                std::vector<std::unique_ptr<UI::Base>> _uiToDelete;

                std::map<std::string, UI::Base*> _labeledUI;

                Graphics::Point _position;

                bool _modal = false; // prevents all states before this one to call think() method

                bool _active = false;

                bool _fullscreen = true; // prevents render all states before this one

                bool _initialized = false;

                Event::StateHandler _activateHandler, _deactivateHandler, _fadeDoneHandler, _pushHandler, _popHandler;

                Event::KeyboardHandler _keyDownHandler, _keyUpHandler;

            protected:
                std::shared_ptr<Input::Mouse> mouse() const;

            private:
                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;

                std::shared_ptr<Input::Mouse> _mouse;
        };
    }
}
