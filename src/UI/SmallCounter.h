#pragma once

#include <memory>
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace UI
    {
        class Image;

        class SmallCounter final : public Falltergeist::UI::Base
        {
            public:
                enum Color
                {
                    WHITE = 1,
                    YELLOW,
                    RED
                };
                enum Type
                {
                    UNSIGNED = 0,
                    SIGNED
                };

                SmallCounter(const Graphics::Point& pos);

                SmallCounter(const SmallCounter&) = delete;

                void operator=(const SmallCounter&) = delete;

                virtual ~SmallCounter() = default;

                Color color() const;

                void setColor(Color color);

                unsigned int length() const;

                void setLength(unsigned int length);

                signed int number() const;

                void setNumber(signed int number);

                Type type() const;

                void setType(Type type);

                void render(bool eggTransparency) override;

                bool opaque(const Graphics::Point &pos) override;

            private:
                Color _color = Color::WHITE;

                signed int _number = 0;

                std::string _numberText = "";

                unsigned int _length = 3;

                Type _type = Type::UNSIGNED;

                std::shared_ptr<Graphics::Sprite> _sprite;

                std::vector<Graphics::Rectangle> _rects;
        };
    }
}
