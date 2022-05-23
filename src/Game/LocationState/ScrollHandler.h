#pragma once

#include "../../Input/Mouse.h"
#include "../../Base/Delegate.h"
#include "../../UI/ScrollHitBox.h"
#include "../../Graphics/Point.h"

namespace Falltergeist::Game::LocationState {
    class ScrollHandler final {
    public:
        ScrollHandler(std::shared_ptr<Input::Mouse> mouse);

        void onMouseScrollDirectionChanged(UI::ScrollHitBox::Direction direction);

        Base::Delegate<Graphics::Point>& scrollDeltaHandler();

        void think(const float &deltaTime);

    private:
        void _restoreCursor();

        void _setCursor(Input::Mouse::Cursor cursor);

        bool _isScrollingCursor(Input::Mouse::Cursor cursor);

        std::shared_ptr<Input::Mouse> _mouse;

        Base::Delegate<Graphics::Point> _scrollDeltaHandler;

        UI::ScrollHitBox::Direction _direction = UI::ScrollHitBox::Direction::NONE;
    };
}
