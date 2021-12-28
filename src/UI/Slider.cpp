#include <memory>
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Game/Game.h"
#include "../UI/Image.h"
#include "../UI/Slider.h"
#include "../UI/Rectangle.h"

namespace Falltergeist
{
    namespace UI
    {
        Slider::Slider(const Point& pos, std::unique_ptr<Image> imageOn, std::unique_ptr<Image> imageOff)
            : Base(pos), _imageOn(std::move(imageOn)), _imageOff(std::move(imageOff)) {
            mouseDragHandler().add([=](Event::Mouse* event) { _onDrag(event); });
            mouseDownHandler().add([=](Event::Mouse* event) { _onMouseDown(event); });
            mouseUpHandler().add([=](Event::Mouse* event) { _onMouseUp(event); });
            _downSound = "sound/sfx/ib1p1xx1.acm";
            _upSound = "sound/sfx/ib1lu1x1.acm";
        }

        void Slider::_onDrag(Event::Mouse* event)
        {
            int newOffset = event->position().x() - _position.x() - static_cast<int>(_thumbSize.width() / 2.f); // stick mouse to the middle of the thumb
            if (newOffset < 0) {
                newOffset = 0;
            } else if (newOffset >= _sliderSize.width() - _thumbSize.width()) {
                newOffset = _sliderSize.width() - _thumbSize.width();
            }

            _sliderOffset.setX(newOffset);
            _value = ((maxValue() - minValue())/ static_cast<float>(_sliderSize.width()))*(float)_sliderOffset.x();
            emitEvent(std::make_unique<Event::Event>("change"), changeHandler());
        }

        void Slider::_onMouseDown(Event::Mouse* event)
        {
            if (!event->leftButton()) {
                return;
            }

            if (!_downSound.empty())
            {
                Game::Game::getInstance()->mixer()->playACMSound(_downSound);
            }
        }

        void Slider::_onMouseUp(Event::Mouse* event) {
            if (!event->leftButton()) {
                return;
            }

            auto offset = event->position() - position() - Point(_thumbSize.width() / 2.f, 0);

            if (!_drag) {
                setValue(_offsetToValue(offset));
            }

            if (!_upSound.empty()) {
                Game::Game::getInstance()->mixer()->playACMSound(_upSound);
            }
        }

        double Slider::minValue() const
        {
            return _minValue;
        }

        void Slider::setMinValue(double value)
        {
            _minValue = value;
        }

        double Slider::maxValue() const
        {
            return _maxValue;
        }

        void Slider::setMaxValue(double value)
        {
            _maxValue = value;
        }

        double Slider::value() const
        {
            return _value;
        }

        void Slider::setValue(double value)
        {
            _value = value;
            _sliderOffset = _valueToOffset(value);
            emitEvent(std::make_unique<Event::Event>("change"), changeHandler());
        }

        Event::Handler& Slider::changeHandler()
        {
            return _changeHandler;
        }

        void Slider::render(bool eggTransparency)
        {
            _imageOn->setPosition(position() + _sliderOffset);
            _imageOff->setPosition(position() + _sliderOffset);
            if (_drag) {
                _imageOn->render(eggTransparency);
            } else {
                _imageOff->render(eggTransparency);
            }

            Falltergeist::UI::Rectangle positionBoundaries(position(), size(), SDL_Color({255, 0, 0, 125}));
            positionBoundaries.render();

            Falltergeist::UI::Rectangle thumbBoundaries(position() + _sliderOffset, _imageOn->size(), SDL_Color({0, 255, 0, 125}));
            thumbBoundaries.render();
        }

        bool Slider::opaque(const Point& pos) {
            return pos >= Point(0, 0) && pos < size();
        }

        const Size& Slider::size() const {
            return _sliderSize;
        }

        double Slider::_offsetToValue(const Point& offset) {
            auto value = ((maxValue() - minValue())/ static_cast<float>(_sliderSize.width())) *( float)offset.x();

            if (value > maxValue()) {
                return maxValue();
            }

            if (value < minValue()) {
                return minValue();
            }

            return value;
        }

        Point Slider::_valueToOffset(double value) {
            return Point(
                static_cast<int>(
                    static_cast<float>(
                        _sliderSize.width() - (_thumbSize.width() / 2)
                    ) / (maxValue() - minValue()) * _value
                ),
                0
            );
        }
    }
}
