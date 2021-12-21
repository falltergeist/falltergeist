#include "../UI/Group.h"

namespace Falltergeist {
    namespace UI {
        Group::Group(const Point& position, const Size& size)
            : Base(position), _size(size) {
        }

        void Group::handle(Event::Mouse *mouseEvent) {
            // TODO check boundaries
            // TODO check hitbox
            // TODO if true then call group event handlers

            // TODO proxy-pass event to each item in the group
        }

        void Group::render(bool eggTransparency) {
            for (auto &item : _items) {
                if (item->visible()) {
                    item->render(position());
                }
            }
        }

        const Size &Group::size() const {
            return _size;
        }

        void Group::addItem(UI::Base *item) {
            _items.push_back(std::unique_ptr<UI::Base>(item));
        }
    }
}
