// Project includes
#include "../UI/ScrollHitBox.h"
#include "../Event/Mouse.h"

// Third-party includes

// stdlib

namespace Falltergeist::UI {

    ScrollHitBox::ScrollHitBox(const Graphics::Size& size, uint8_t hitAreaSize) : UI::Base({0, 0}, size), _hitAreaSize(hitAreaSize) {
        mouseDownHandler().add([=](Event::Mouse* event){
            if (_isBoxHit(event->position())) {
                event->stopPropagation();
            }
        });

        mouseUpHandler().add([=](Event::Mouse* event) {
            if (_isBoxHit(event->position())) {
                event->stopPropagation();
            }
        });

        mouseMoveHandler().add(std::bind(&ScrollHitBox::_onMouseMove, this, std::placeholders::_1));
    }

    bool ScrollHitBox::opaque(const Graphics::Point& at) {
        return true;
    }

    Falltergeist::Base::Delegate<ScrollHitBox::Direction>& ScrollHitBox::directionChangeHandler() {
        return _directionChangeHandler;
    }

    ScrollHitBox::Direction ScrollHitBox::direction() const {
        return _direction;
    }

    void ScrollHitBox::_onMouseMove(Event::Mouse* event) {
        auto at = event->position();

        bool isScrollingLeft = _isScrollingLeft(at);
        bool isScrollingTop = _isScrollingTop(at);
        bool isScrollingRight = _isScrollingRight(at);
        bool isScrollingBottom = _isScrollingBottom(at);

        if (isScrollingLeft || isScrollingTop || isScrollingRight || isScrollingBottom) {
            event->stopPropagation();
        }

        if (isScrollingLeft && isScrollingTop) {
            _setDirection(Direction::NORTH_WEST);
            return;
        }

        if (isScrollingLeft && isScrollingBottom) {
            _setDirection(Direction::SOUTH_WEST);
            return;
        }

        if (isScrollingRight && isScrollingTop) {
            _setDirection(Direction::NORTH_EAST);
            return;
        }

        if (isScrollingRight && isScrollingBottom) {
            _setDirection(Direction::SOUTH_EAST);
            return;
        }

        if (isScrollingLeft) {
            _setDirection(Direction::WEST);
            return;
        }

        if (isScrollingTop) {
            _setDirection(Direction::NORTH);
            return;
        }

        if (isScrollingRight) {
            _setDirection(Direction::EAST);
            return;
        }

        if (isScrollingBottom) {
            _setDirection(Direction::SOUTH);
            return;
        }

        _setDirection(Direction::NONE);
    }

    void ScrollHitBox::_setDirection(Direction direction) {
        if (_direction == direction) {
            return;
        }

        _direction = direction;
        _directionChangeHandler.invoke(_direction);
    }

    bool ScrollHitBox::_isScrollingTop(const Graphics::Point& at) const {
        return at.y() >= position().y() && at.y() < position().y() + _hitAreaSize;
    }

    bool ScrollHitBox::_isScrollingBottom(const Graphics::Point& at) const {
        return at.y() < position().y() + size().height() && at.y() >= position().y() + size().height() - _hitAreaSize;
    }

    bool ScrollHitBox::_isScrollingLeft(const Graphics::Point& at) const {
        return at.x() >= position().x() && at.x() < position().x() + _hitAreaSize;
    }

    bool ScrollHitBox::_isScrollingRight(const Graphics::Point& at) const {
        return at.x() < position().x() + size().width() && at.x() >= position().x() + size().width() - _hitAreaSize;
    }

    bool ScrollHitBox::_isBoxHit(const Graphics::Point& at) const {
        return _isScrollingTop(at) || _isScrollingBottom(at) || _isScrollingLeft(at) || _isScrollingRight(at);
    }
}
