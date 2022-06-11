#pragma once

// Project includes
#include "Format/Txt/CityFile.h"
#include "Graphics/TranslucentMask.h"
#include "UI/TextArea.h"

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    class WorldMapCity final {
        public:
            WorldMapCity(Format::Txt::City city, std::shared_ptr<Graphics::TranslucentMask> sprite);

            const Graphics::Point& worldPos() const;

            bool state() const;

            Format::Txt::City::Size size() const;

            void render(const Graphics::Point& point) const;

        private:
            Format::Txt::City _city;

            Graphics::Point _worldPos;

            bool _state;

            std::shared_ptr<Graphics::TranslucentMask> _sprite;

            std::unique_ptr<UI::TextArea> _name;
    };
}
