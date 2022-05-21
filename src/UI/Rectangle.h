#pragma once

#include "../Graphics/Color.h"
#include "../Graphics/Point.h"
#include "../UI/Base.h"

namespace Falltergeist::UI {
    class Rectangle final : public Base {
    public:
        Rectangle(const Graphics::Point& pos, const Graphics::Size& size, Graphics::Color color);

        void render(bool eggTransparency = false) override;

        bool opaque(const Graphics::Point& pos) override;

        const Graphics::Size& size() const override;

    private:
        Graphics::Size _size;

        Graphics::Color _color;
    };
}
