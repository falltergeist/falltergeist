// Project includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../UI/Rectangle.h"

// Third-party includes

// stdlib

namespace Falltergeist::UI {
    Rectangle::Rectangle(const Graphics::Point &pos, const Graphics::Size &size, Graphics::Color color) : Base(pos), _size(size), _color(color) {
    }

    void Rectangle::render(bool eggTransparency) {
        Game::Game::getInstance()->renderer()->drawRect(position(), _size, _color);
    }

    bool Rectangle::opaque(const Graphics::Point &pos) {
        return false;
    }

    const Graphics::Size& Rectangle::size() const {
        return _size;
    }
}
