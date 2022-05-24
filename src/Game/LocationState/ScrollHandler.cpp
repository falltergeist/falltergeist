#include "../../Game/LocationState/ScrollHandler.h"

namespace Falltergeist::Game::LocationState {

    using Direction = UI::ScrollHitBox::Direction;
    using Cursor = Input::Mouse::Cursor;

    ScrollHandler::ScrollHandler(std::shared_ptr<Input::Mouse> mouse) : _mouse(mouse) {
    }

    Base::Delegate<Graphics::Point>& ScrollHandler::scrollDeltaHandler() {
        return _scrollDeltaHandler;
    }

    void ScrollHandler::onMouseScrollDirectionChanged(UI::ScrollHitBox::Direction direction) {
        if (_direction == Direction::NONE && direction != Direction::NONE) {
            _previousCursor = _mouse->cursor();
        }

        _direction = direction;
        switch (direction) {
            case Direction::WEST: {
                _setCursor(Cursor::SCROLL_W);
                break;
            }
            case Direction::NORTH_WEST: {
                _setCursor(Cursor::SCROLL_NW);
                break;
            }
            case Direction::NORTH: {
                _setCursor(Cursor::SCROLL_N);
                break;
            }
            case Direction::NORTH_EAST: {
                _setCursor(Cursor::SCROLL_NE);
                break;
            }
            case Direction::EAST: {
                _setCursor(Cursor::SCROLL_E);
                break;
            }
            case Direction::SOUTH_EAST: {
                _setCursor(Cursor::SCROLL_SE);
                break;
            }
            case Direction::SOUTH: {
                _setCursor(Cursor::SCROLL_S);
                break;
            }
            case Direction::SOUTH_WEST: {
                _setCursor(Cursor::SCROLL_SW);
                break;
            }
            case Direction::NONE: {
                _restoreCursor();
                break;
            }
        }
    }

    void ScrollHandler::think(const float &deltaTime) {
        float scrollSpeed = 5.0f /* pixels */ / 10.0f /* ms */;
        int scrollDelta = scrollSpeed * deltaTime;

        bool isScrollLeft = (_direction == Direction::WEST || _direction == Direction::NORTH_WEST || _direction == Direction::SOUTH_WEST);
        bool isScrollRight = (_direction == Direction::EAST || _direction == Direction::NORTH_EAST || _direction == Direction::SOUTH_EAST);
        bool isScrollTop = (_direction == Direction::NORTH || _direction == Direction::NORTH_EAST || _direction == Direction::NORTH_WEST);
        bool isScrollBottom = (_direction == Direction::SOUTH || _direction == Direction::SOUTH_EAST || _direction == Direction::SOUTH_WEST);

        Graphics::Point delta = Graphics::Point(
            isScrollLeft ? -scrollDelta : (isScrollRight ? scrollDelta : 0),
            isScrollTop ? -scrollDelta : (isScrollBottom ? scrollDelta : 0)
        );
        _scrollDeltaHandler.invoke(delta);
    }

    void ScrollHandler::_restoreCursor() {
        _mouse->setCursor(_previousCursor);
    }

    void ScrollHandler::_setCursor(Input::Mouse::Cursor cursor) {
        _mouse->setCursor(cursor);
    }
}
