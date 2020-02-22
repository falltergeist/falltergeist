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
    namespace Format
    {
        namespace Frm
        {
            class File;
        }
    }
    namespace UI
    {
        class Image : public Base
        {
            public:
                Image(const Graphics::Sprite &sprite);
                Image(Format::Frm::File* frm, unsigned int direction);
                virtual ~Image() = default;

                virtual void render(bool eggTransparency = false) override;

                virtual void render(const Size &size, bool eggTransparency = false) override;

                bool opaque(unsigned int x, unsigned int y);
                virtual bool opaque(const Point &pos) override;

                virtual Size size() const override;
            private:
                Graphics::Sprite _sprite;
        };
    }
}
