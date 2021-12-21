#pragma once

#include <string>
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Sprite;
    }
    namespace UI
    {
        class Image final : public Base
        {
            public:
                Image(std::unique_ptr<Graphics::Sprite> sprite);
                virtual ~Image() = default;

                void render(bool eggTransparency = false) override;

                void render(const Size &size, bool eggTransparency = false) override;

                void render(const Point& position) override;

                bool opaque(const Point &position) override;

                const Size& size() const override;

            private:
                std::unique_ptr<Graphics::Sprite> sprite;
        };
    }
}
