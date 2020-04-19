#pragma once

#include <map>
#include <memory>
#include <vector>
#include "../Event/EventTarget.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Graphics/Point.h"
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
        using Graphics::Point;

        class State : public Event::EventTarget
        {
            public:
                State();
                State(const State&) = delete;
                State& operator=(const State&) = delete;
                virtual ~State() = default;

                template<class T,
                        class ...TCtorArgs,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> makeUI(TCtorArgs&&... args)
                {
                    auto p = std::make_shared<T>(std::forward<TCtorArgs>(args)...);
                    addUI(p);
                    return p;
                }

                template<class T,
                        class ...TCtorArgs,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> makeNamedUI(std::string name, TCtorArgs&&... args)
                {
                    auto p = std::make_shared<T>(std::forward<TCtorArgs>(args)...);
                    addUI(std::move(name), p);
                    return p;
                }

                template<class T,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> addUI(T* ui) {
                    // TODO: this is a temporary API-compatible version of addUI that allows existing code to compile
                    // TODO: ideally, the existing code should be refactored to use smart pointers (the other overloads)
                    return this->addUI(std::shared_ptr<T>{ui});
                }

                template<class T,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T>  addUI(std::shared_ptr<T> ui)
                {
                    // ui->setPosition(ui->position() - ui->offset() + position());  // TODO: unsure why this is needed
                    _ui.emplace_back(ui);
                    return ui;
                }

                template<class T,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T>  addUI(std::unique_ptr<T> ui)
                {
                    return addUI(std::shared_ptr<T>{std::move(ui)});
                }

                template<class T,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> addUI(std::string name, std::shared_ptr<T> ui)
                {
                    auto ret = addUI(ui);
                    _labeledUI.insert({ std::move(name), ui });
                    return ret;
                }

                template<class T,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> addUI(std::string name, std::unique_ptr<T> ui)
                {
                    auto ret = addUI(std::shared_ptr<T>{std::move(ui)});
                    _labeledUI.insert({ std::move(name), ret });
                    return ret;
                }

                template<class T,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> addUI(std::string name, T* ui) {
                    // TODO: this is a temporary API-compatible version of addUI that allows existing code to compile
                    // TODO: ideally, the existing code should be refactored to use smart pointers (the other overloads)
                    return this->addUI(std::move(name), std::shared_ptr<T>{ui});
                }

                template<typename T = UI::Base,
                        typename = std::enable_if_t<std::is_base_of<UI::Base, T>::value>>
                std::shared_ptr<T> getUI(const std::string& name) const {
                    return std::dynamic_pointer_cast<T>(getUIInternal(name));
                }

                void popUI();

                // @todo: remove getters/setters for x, y?
                virtual int x() const;
                virtual void setX(int x);

                virtual int y() const;
                virtual void setY(int y);

                virtual const Point& position() const;
                virtual void setPosition(const Point& pos);

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

            private:
                std::shared_ptr<UI::Base> getUIInternal(const std::string& name) const;

            protected:
                std::vector<std::shared_ptr<UI::Base>> _ui;
                std::vector<std::shared_ptr<UI::Base>> _uiToDelete;
                std::map<std::string, std::shared_ptr<UI::Base>> _labeledUI;

                Point _position;

                bool _modal = false; // prevents all states before this one to call think() method
                bool _active = false;

                bool _fullscreen = true; // prevents render all states before this one
                bool _initialized = false;

                Event::StateHandler _activateHandler;
                Event::StateHandler _deactivateHandler;
                Event::StateHandler _fadeDoneHandler;
                Event::StateHandler _pushHandler;
                Event::StateHandler _popHandler;
                Event::KeyboardHandler _keyDownHandler;
                Event::KeyboardHandler _keyUpHandler;
        };
    }
}
