// Project includes
#include "WorldMapCity.h"
#include "ResourceManager.h"

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    WorldMapCity::WorldMapCity(Format::Txt::City city, std::shared_ptr<Graphics::TranslucentMask> sprite) {
        _city = city;
        _state = _city.startState;
        _worldPos = Graphics::Point(_city.worldX, _city.worldY);
        _sprite = sprite;
        _sprite->setColor({0, 0xff, 0, 0xff});
        _name = std::make_unique<UI::TextArea>(city.name, _worldPos);
        _name->setFont(ResourceManager::getInstance()->font("font0.fon"), {0, 0xff, 0, 0xff});
        _name->setWidth(_name->textSize().width());
        _name->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
    }

    const Graphics::Point& WorldMapCity::worldPos() const {
        return _worldPos;
    }

    bool WorldMapCity::state() const {
        return _state;
    }

    Format::Txt::City::Size WorldMapCity::size() const {
        return _city.size;
    }

    void WorldMapCity::render(const Graphics::Point& point) const {
        _sprite->render(point);
        auto spriteSize = _sprite->size();
        auto nameOffset = Graphics::Point(spriteSize.width() / 2 - _name->size().width() / 2, spriteSize.height() + 1);
        _name->setPosition(point + nameOffset);
        _name->render();
    }
}
