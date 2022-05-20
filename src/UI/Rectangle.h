#pragma once

#include "../Graphics/Color.h"
#include "../Graphics/Point.h"
#include "../UI/Base.h"

namespace Falltergeist::UI {
    class Rectangle final : public Base {
    public:
        Rectangle(const Point& pos, const Size& size, Graphics::Color color);

        void render(bool eggTransparency = false) override;

        bool opaque(const Point& pos) override;

        const Size& size() const override;

    private:
        Size _size;

        Graphics::Color _color;
    };
}
