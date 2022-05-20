#pragma once

#include <memory>
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace UI
    {
        class Image;

        class BigCounter final : public Falltergeist::UI::Base
        {
            public:
                enum class Color
                {
                    WHITE = 1,
                    RED
                };

                BigCounter(const Point& pos = Point(), unsigned int length = 2);

                virtual ~BigCounter() = default;

                BigCounter(const BigCounter&) = delete;

                void operator=(const BigCounter&) = delete;

                void setColor(Color color);

                Color color();

                void setNumber(unsigned int number);

                unsigned int number();

                void render(bool eggTransparency) override;

                bool opaque(const Point &pos) override;

            private:
                Color _color = Color::WHITE;

                unsigned int _number = 0;

                std::string _numberText = "";

                unsigned int _length = 2;

                std::shared_ptr<Graphics::Sprite> _sprite;

                std::vector<SDL_Rect> _rects;
        };
    }
}
