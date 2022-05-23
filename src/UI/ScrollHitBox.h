#pragma once

#include "../UI/Base.h"

namespace Falltergeist::UI {
    class ScrollHitBox final : public UI::Base {
    public:
        enum class Direction : int{
            NONE = 0,
            WEST = 1,
            NORTH_WEST = 2,
            NORTH = 3,
            NORTH_EAST = 4,
            EAST = 5,
            SOUTH_EAST = 6,
            SOUTH = 7,
            SOUTH_WEST = 8,
        };

    public:
        ScrollHitBox(const Graphics::Size& size, uint8_t hitAreaSize = 8);

        bool opaque(const Graphics::Point& pos) override;

        Falltergeist::Base::Delegate<Direction>& directionChangeHandler();

        Direction direction() const;

    private:
        bool _isScrollingTop(const Graphics::Point& at) const;

        bool _isScrollingBottom(const Graphics::Point& at) const;

        bool _isScrollingLeft(const Graphics::Point& at) const;

        bool _isScrollingRight(const Graphics::Point& at) const;

        bool _isBoxHit(const Graphics::Point& at) const;

        void _onMouseMove(Event::Mouse* event);

        void _setDirection(Direction direction);

        Falltergeist::Base::Delegate<Direction> _directionChangeHandler;

        Direction _direction = Direction::NONE;

        uint8_t _hitAreaSize;
    };
}
