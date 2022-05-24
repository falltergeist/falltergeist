#pragma once

// Project includes
#include "../UI/Base.h"
#include "../UI/ImageList.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist {
    namespace Event {
        class Mouse;
    }
    namespace UI {
        class Slider : public Falltergeist::UI::Base {
        public:
            Slider(const Graphics::Point& pos, std::unique_ptr<Image> imageOn, std::unique_ptr<Image> imageOff);

            virtual ~Slider() = default;

            const Graphics::Size& size() const override;

            bool opaque(const Graphics::Point& pos) override;

            void render(bool eggTransparency) override;

            double minValue() const;

            void setMinValue(double value);

            double maxValue() const;

            void setMaxValue(double value);

            double value() const;

            void setValue(double value);

            Event::Handler& changeHandler();

        private:
            Graphics::Size _sliderSize = Graphics::Size(241, 14);

            Graphics::Point _sliderOffset = Graphics::Point(0, 0);

            Graphics::Size _thumbSize = Graphics::Size(21, 14);

            std::unique_ptr<Image> _imageOn;

            std::unique_ptr<Image> _imageOff;

            double _minValue = 0.0;

            double _maxValue = 1.0;

            double _value = 0.0;

            std::string _downSound;

            std::string _upSound;

            Event::Handler _changeHandler;

            void _onDrag(Event::Mouse* event);

            void _onMouseDown(Event::Mouse* event);

            void _onMouseUp(Event::Mouse* event);

            double _offsetToValue(const Graphics::Point& offset);

            Graphics::Point _valueToOffset(double value);
        };
    }
}
