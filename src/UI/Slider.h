#pragma once

#include <string>
#include "../UI/Base.h"
#include "../UI/ImageList.h"

namespace Falltergeist
{
    namespace Event
    {
        class Mouse;
    }
    namespace UI
    {
        class Slider : public Falltergeist::UI::Base
        {
            public:
                Slider(const Point& pos, std::unique_ptr<Image> imageOn, std::unique_ptr<Image> imageOff);

                virtual ~Slider() = default;

                const Size& size() const override;

                bool opaque(const Point &pos) override;

                void render(bool eggTransparency) override;

                double minValue() const;

                void setMinValue(double value);

                double maxValue() const;

                void setMaxValue(double value);

                double value() const;

                void setValue(double value);

                Event::Handler& changeHandler();

            private:
                Size _sliderSize = Size(241, 14);

                Point _sliderOffset = Point(0, 0);

                Size _thumbSize = Size(21, 14);

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

                double _offsetToValue(const Point& offset);

                Point _valueToOffset(double value);
        };
    }
}
