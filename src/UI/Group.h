#pragma once

#include "../UI/Base.h"
#include <vector>

namespace Falltergeist {
    namespace UI {

        /**
         * Group represents a group of UI elements that should be rendered and
         * managed together Group renders items with its own offset Group
         * handles mouse events by it boundaries or/and hitmask
         */
        class Group final : public Base {
        public:
            Group(const Point &position, const Size& size);

            void handle(Event::Mouse *mouseEvent) override;

            void render(bool eggTransparency = false) override;

            const Size& size() const override;

            void addItem(UI::Base *item);

        private:
            std::vector<std::unique_ptr<UI::Base>> _items;

            Size _size;
        };
    }
}
