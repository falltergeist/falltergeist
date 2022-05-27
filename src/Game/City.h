#pragma once

// Project includes
#include "Format/Txt/CityFile.h"
#include "Graphics/Point.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        class City
        {
            public:
                City(Format::Txt::City city);

                const Graphics::Point& worldPos() const;

                bool state() const;

                Format::Txt::City::Size size() const;

            private:
                Format::Txt::City _city;

                Graphics::Point _worldPos;

                bool _state;
        };
    }
}
