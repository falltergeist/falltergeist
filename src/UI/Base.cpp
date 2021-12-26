#include <memory>
#include "../Game/Game.h"
#include "../Game/DudeObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace UI
    {
        using namespace Base;

        Base::Base(int x, int y) : Base(Point(x, y))
        {
        }

        Base::Base(const Point& pos) : Event::EventTarget(Game::Game::getInstance()->eventDispatcher())
        {
            _position = pos;
        }

        Base::~Base()
        {
        }

        int Base::x() const
        {
            return (position() + offset()).x();
        }

        void Base::setX(int value)
        {
            setPosition(Point(value, position().y()));
        }

        int Base::y() const
        {
            return _position.y() + _offset.y();
        }

        void Base::setY(int value)
        {
            setPosition(Point(position().x(), value));
        }

        void Base::think(const float &deltaTime)
        {
        }

        void Base::render(bool eggTransparency)
        {
        }

        void Base::setVisible(bool value)
        {
            _visible = value;
        }

        bool Base::visible() const
        {
            return _visible;
        }

        Point Base::position() const
        {
            // TODO get rid of offset in position()
            return _position + _offset;
        }

        void Base::setPosition(const Point& pos)
        {
            _position = pos;
        }

        Point Base::offset() const
        {
            return _offset;
        }

        void Base::setOffset(const Point& pos)
        {
            _offset = pos;
        }

        void Base::setOffset(int x, int y)
        {
            setOffset(Point(x, y));
        }

        Size Base::size() const
        {
            return Size(0, 0);
        }

        bool Base::opaque(const Point &pos)
        {
            return false;
        }

        void Base::handle(Event::Event* event)
        {
            if (event->isHandled()) {
                return;
            }

            // TODO: get rid of dynamic_casts by using template member function?
            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event)) {
                handle(mouseEvent);
            }

            if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
            {
                switch (keyboardEvent->originalType())
                {
                    case Event::Keyboard::Type::KEY_UP:
                    {
                        emitEvent(std::make_unique<Event::Keyboard>(*keyboardEvent), keyUpHandler());
                        break;
                    }
                    case Event::Keyboard::Type::KEY_DOWN:
                    {
                        emitEvent(std::make_unique<Event::Keyboard>(*keyboardEvent), keyDownHandler());
                        break;
                    }
                }
            }
        }

        void Base::handle(Event::Mouse* mouseEvent)
        {
            if (!_visible) {
                return;
            }
            using Mouse = Event::Mouse;
            Point relPos = mouseEvent->position() - this->position();

            if (!mouseEvent->obstacle() && this->opaque(relPos)) // mouse cursor is over the element
            {
                switch (mouseEvent->originalType())
                {
                    case Mouse::Type::MOVE:
                    {

                        if (_leftButtonPressed)
                        {
                            emitEvent(std::make_unique<Mouse>(*mouseEvent, _drag ? "mousedrag" : "mousedragstart"),
                                      _drag ? mouseDragHandler() : mouseDragStartHandler());
                            _drag = true;
                        }
                        if (!_hovered)
                        {
                            _hovered = true;
                            emitEvent(std::make_unique<Mouse>(*mouseEvent, "mousein"), mouseInHandler());
                        }
                        else
                        {
                            emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mousemove"), mouseMoveHandler());
                        }
                        break;
                    }
                    case Mouse::Type::BUTTON_DOWN:
                    {
                        emitEvent(std::make_unique<Event::Mouse>(*mouseEvent), mouseDownHandler());
                        switch (mouseEvent->button())
                        {
                            case Mouse::Button::LEFT:
                            {
                                if (_leftButtonPressed == false) {
                                    _leftButtonPressed = true;
                                }

                                break;
                            }
                            case Mouse::Button::RIGHT:
                            {
                                _rightButtonPressed = true;
                                break;
                            }
                            default:
                                break;
                        }
                        // mousedown event can not be "interesting" for any other UI's that "behind" this UI,
                        // so we can safely stop event capturing now
                        mouseEvent->stopPropagation();
                        break;
                    }
                    case Mouse::Type::BUTTON_UP:
                    {
                        emitEvent(std::make_unique<Event::Mouse>(*mouseEvent), mouseUpHandler());
                        switch (mouseEvent->button())
                        {
                            case Mouse::Button::LEFT:
                            {
                                if (_leftButtonPressed)
                                {
                                    if (_drag)
                                    {
                                        _drag = false;
                                        emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mousedragstop"), mouseDragStopHandler());
                                    }
                                    emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mouseclick"), mouseClickHandler());
                                }
                                _leftButtonPressed = false;
                                break;
                            }
                            case Mouse::Button::RIGHT:
                            {
                                if (_rightButtonPressed)
                                {
                                    emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mouseclick"), mouseClickHandler());
                                }
                                _rightButtonPressed = false;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                }
                mouseEvent->setObstacle(true);
            }
            else // mouse cursor is outside of this element or other element is in front
            {
                // stop processing if this element has no active interactions with the mouse
                if (!_hovered && !_leftButtonPressed && !_rightButtonPressed && !_drag)
                {
                    return;
                }
                switch (mouseEvent->originalType())
                {
                    case Mouse::Type::MOVE:
                    {
                        if (_drag)
                        {
                            emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mousedrag"), mouseDragHandler());
                        }
                        if (_hovered)
                        {
                            _hovered = false;
                            emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mouseout"), mouseOutHandler());
                        }
                        break;
                    }
                    case Mouse::Type::BUTTON_UP:
                    {
                        switch (mouseEvent->button())
                        {
                            case Mouse::Button::LEFT:
                            {
                                if (_leftButtonPressed)
                                {
                                    if (_drag)
                                    {
                                        _drag = false;
                                        emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mousedragstop"), mouseDragStopHandler());
                                    }

                                    emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mouseup"), mouseUpHandler());
                                    _leftButtonPressed = false;
                                }
                                break;
                            }
                            case Mouse::Button::RIGHT:
                            {
                                if (_rightButtonPressed)
                                {
                                    emitEvent(std::make_unique<Event::Mouse>(*mouseEvent, "mouseup"), mouseUpHandler());
                                    _rightButtonPressed = false;
                                }
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
            return;
        }

        unsigned Base::width() const
        {
            return size().width();
        }

        unsigned Base::height() const
        {
            return size().height();
        }

        Event::KeyboardHandler& Base::keyDownHandler()
        {
            return _keyDownHandler;
        }

        Event::KeyboardHandler& Base::keyUpHandler()
        {
            return _keyUpHandler;
        }

        Event::MouseHandler& Base::mouseDragStartHandler()
        {
            return _mouseDragStartHandler;
        }

        Event::MouseHandler& Base::mouseDragHandler()
        {
            return _mouseDragHandler;
        }

        Event::MouseHandler& Base::mouseDragStopHandler()
        {
            return _mouseDragStopHandler;
        }

        Event::MouseHandler& Base::mouseInHandler()
        {
            return _mouseInHandler;
        }

        Event::MouseHandler& Base::mouseMoveHandler()
        {
            return _mouseMoveHandler;
        }

        Event::MouseHandler& Base::mouseOutHandler()
        {
            return _mouseOutHandler;
        }

        Event::MouseHandler& Base::mouseClickHandler()
        {
            return _mouseClickHandler;
        }

        Event::MouseHandler& Base::mouseDownHandler()
        {
            return _mouseDownHandler;
        }

        Event::MouseHandler& Base::mouseUpHandler()
        {
            return _mouseUpHandler;
        }

        void Base::render(const Size &size, bool eggTransparency)
        {
            render(eggTransparency);
        }

        void Base::setLight(bool light)
        {
            _light = light;
        }

        bool Base::light()
        {
            return _light;
        }

        Graphics::TransFlags::Trans Base::trans() const
        {
            return _trans;
        }

        void Base::setTrans(Graphics::TransFlags::Trans value)
        {
            _trans = value;
        }

        void Base::setOutline(int outline)
        {
            _outline=outline;
        }

        void Base::setLightLevel(unsigned int level)
        {
            _lightLevel = level;
        }
    }
}
