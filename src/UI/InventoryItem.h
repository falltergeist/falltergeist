#pragma once

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Format/Enums.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace Event
    {
        class Mouse;
    }
    namespace Game
    {
        class ItemObject;
    }
    namespace UI
    {
        class InventoryItem : public Falltergeist::UI::Base
        {
            public:
                enum class Type
                {
                    INVENTORY = 0,
                    SLOT,
                    DRAG
                };

                InventoryItem(const std::shared_ptr<Game::ItemObject> &item, const Point& pos = Point());
                ~InventoryItem() override;

                Type type() const;
                void setType(Type value);

                const std::shared_ptr<Game::ItemObject> &item();
                void setItem(const std::shared_ptr<Game::ItemObject> &item);

                void render(bool eggTransparency = false) override;
                Size size() const override;

                virtual bool opaque(const Point &pos) override;

                void onMouseLeftDown(Event::Mouse* event);
                void onMouseDragStart(Event::Mouse* event);
                void onMouseDrag(Event::Mouse* event);
                void onMouseDragStop(Event::Mouse* event);

                void onArmorDragStop(Event::Mouse* event);
                void onHandDragStop(Event::Mouse* event, HAND hand);

                Event::MouseHandler& itemDragStopHandler();

            private:
                std::shared_ptr<Game::ItemObject> _item;
                Type _type = Type::INVENTORY;
                Type _oldType = Type::INVENTORY;

                Event::MouseHandler _itemDragStopHandler;
        };
    }
}
