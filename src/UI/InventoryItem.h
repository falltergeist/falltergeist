#pragma once

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
        class ItemsList;

        class InventoryItem : public Falltergeist::UI::Base
        {
            public:
                enum class Type
                {
                    INVENTORY = 0,
                    SLOT,
                    DRAG
                };

                InventoryItem(Game::ItemObject* item, const Point& pos = Point());
                ~InventoryItem() override;

                Type type() const;
                void setType(Type value);

                Game::ItemObject* item();
                void setItem(Game::ItemObject* item);

                void render(bool eggTransparency = false) override;
                Size size() const override;

                virtual bool opaque(const Point &pos) override;

                void onMouseLeftDown(Event::Mouse* event);

                void onMouseDragStart(Event::Mouse* event);

                void onMouseDrag(Event::Mouse* event);

                void onMouseDragStop(Event::Mouse* event);

                void onArmorDragStop(Event::Mouse* event, ItemsList* target);

                void onHandDragStop(Event::Mouse* event, HAND hand, ItemsList* target);

                Event::MouseHandler& itemDragStopHandler();

            private:
                Game::ItemObject* _item = nullptr;

                Type _type = Type::INVENTORY;

                Type _oldType = Type::INVENTORY;

                Event::MouseHandler _itemDragStopHandler;
        };
    }
}
