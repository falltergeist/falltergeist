#pragma once

// Project includes
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

// Third-party includes

// stdlib
#include <string>

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

                virtual void render(bool eggTransparency = false) override;

                virtual void render(const Graphics::Size &size, bool eggTransparency = false) override;

                virtual bool opaque(const Graphics::Point &position) override;

                const Graphics::Size& size() const override;

            private:
                std::unique_ptr<Graphics::Sprite> _sprite;
        };
    }
}
