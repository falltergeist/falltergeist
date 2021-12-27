#pragma once

#include <memory>
#include "../Event/EventTarget.h"
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"
#include "../Graphics/TransFlags.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture;
    }

    namespace UI
    {
        using Graphics::Point;
        using Graphics::Size;

        class Base : public Event::EventTarget
        {
            public:

                Base(int x = 0, int y = 0);
                Base(const Point& pos);
                ~Base() override;

                int x() const;
                void setX(int value);

                int y() const;
                void setY(int value);

                virtual unsigned width() const;
                virtual unsigned height() const;

                virtual Point position() const;

                // TODO get rid of this. This should be position()
                virtual const Point& rawPosition() const;

                virtual void setPosition(const Point& pos);

                virtual Point offset() const;
                virtual void setOffset(const Point& pos);
                void setOffset(int x, int y);

                virtual bool visible() const;
                virtual void setVisible(bool value);

                /**
                 * @brief Handles OS events coming from the State::handle().
                 * Used in Event Capturing process.
                 * This method is called first in the main loop (before think() and render()).
                 */
                virtual void handle(Event::Event* event);
                /**
                 * @brief Process any real-time actions at each frame.
                 * This method is called after handle() but before render() in the main loop.
                 */
                virtual void think(const float &deltaTime);
                /**
                 * @brief Render this UI element on game window.
                 * This method is called last in the main loop (after handle() and think()).
                 */
                virtual void render(bool eggTransparency = false);
                virtual void render(const Size& size, bool eggTransparency = false);

                /**
                 * @brief Handles mouse events from OS.
                 */
                virtual void handle(Event::Mouse* mouseEvent);

                virtual Size size() const;

                virtual bool opaque(const Point &pos);

                Event::KeyboardHandler& keyDownHandler();
                Event::KeyboardHandler& keyUpHandler();

                // TODO: maybe not all elements should have drag events?
                Event::MouseHandler& mouseDragStartHandler();
                Event::MouseHandler& mouseDragHandler();
                Event::MouseHandler& mouseDragStopHandler();
                Event::MouseHandler& mouseInHandler();
                Event::MouseHandler& mouseMoveHandler();
                Event::MouseHandler& mouseOutHandler();
                Event::MouseHandler& mouseClickHandler();
                Event::MouseHandler& mouseDownHandler();
                Event::MouseHandler& mouseUpHandler();
                // TODO: mouse hover? (will require additional hoverDelay property)

                virtual void setLight(bool light);
                virtual bool light();
                virtual void setLightLevel(unsigned int level);
                // object translucency mode
                Graphics::TransFlags::Trans trans() const;
                // sets object translucency mode
                void setTrans(Graphics::TransFlags::Trans value);

                void setOutline(int outline);

            protected:
                Point _position;
                Point _offset;
                bool _light = false;
                Graphics::TransFlags::Trans _trans = Graphics::TransFlags::Trans::DEFAULT;

                bool _leftButtonPressed = false;
                bool _rightButtonPressed = false;
                bool _drag = false;
                bool _hovered = false;
                bool _visible = true;

                Event::KeyboardHandler _keyDownHandler, _keyUpHandler;
                Event::MouseHandler _mouseDragStartHandler, _mouseDragHandler, _mouseDragStopHandler,
                                    _mouseInHandler, _mouseMoveHandler, _mouseOutHandler,
                                    _mouseClickHandler, _mouseDownHandler, _mouseUpHandler;

                int _outline = 0;
                unsigned int _lightLevel;
        };
    }
}
