#pragma once

#include "../Graphics/Point.h"
#include "../UI/IResourceManager.h"
#include "../UI/Image.h"
#include <memory>
#include <vector>

namespace Falltergeist {
    namespace UI {
        class Base;
    }
    namespace Input {
        using Graphics::Point;

        class Mouse final {
          public:
            // TODO: need to consider getting rid of mouse cursor state stack,
            // it's not convenient to use
            enum class Cursor : unsigned {
                NONE = 0,
                BIG_ARROW = 1,
                SCROLL_W = 2,
                SCROLL_W_X = 3,
                SCROLL_NW = 4,
                SCROLL_NW_X = 5,
                SCROLL_N = 6,
                SCROLL_N_X = 7,
                SCROLL_NE = 8,
                SCROLL_NE_X = 9,
                SCROLL_E = 10,
                SCROLL_E_X = 11,
                SCROLL_SE = 12,
                SCROLL_SE_X = 13,
                SCROLL_S = 14,
                SCROLL_S_X = 15,
                SCROLL_SW = 16,
                SCROLL_SW_X = 17,
                HEXAGON_RED = 18,
                ACTION = 19,
                ACTION_REVERSE = 20,
                WAIT = 21,
                HAND = 22,
                SMALL_UP_ARROW = 23,
                SMALL_DOWN_ARROW = 24,
                USE = 25
            };

            // TODO: this is specific to CursorDropdown state, should not be
            // here
            enum class Icon : unsigned {
                ROTATE = 1,
                SKILL,
                INVENTORY,
                CANCEL,
                LOOK,
                TALK,
                PUSH,
                UNLOAD,
                USE
            };

            Mouse(const std::shared_ptr<UI::IResourceManager>& resourceManager);

            ~Mouse();

            const Point& position() const;

            void setPosition(const Point& pos);

            void pushState(Cursor state);

            void popState();

            Cursor state() const;

            void setState(Cursor state);

            const std::vector<Cursor>& states();

            bool scrollState();

            void render();

            void renderOutline();

            void think(const float& deltaTime);

            UI::Base* ui();

          private:
            std::shared_ptr<UI::IResourceManager> _resourceManager;

            std::vector<Cursor> _states;

            std::unique_ptr<UI::Base> _ui;

            void _setType(Cursor type);
        };
    }
}
