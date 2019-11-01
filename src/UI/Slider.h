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
                Slider(const Point& pos);
                Slider(int x, int y);
                ~Slider() override;

                void handle(Event::Event* event) override;

                Size size() const override;

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
                ImageList _imageList;
                double _minValue = 0.0;
                double _maxValue = 1.0;
                double _value = 0.0;
                std::string _downSound;
                std::string _upSound;
                Event::Handler _changeHandler;

                void _onDrag(Event::Mouse* event);
                void _onLeftButtonDown(Event::Mouse* event);
                void _onLeftButtonUp(Event::Mouse* event);
        };
    }
}
