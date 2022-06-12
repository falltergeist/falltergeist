#pragma once

// Project includes
#include "../Format/Enums.h"
#include "../UI/Base.h"

// Third-party includes

// stdlib

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

                InventoryItem(Game::ItemObject* item, const Graphics::Point& pos = Graphics::Point());

                ~InventoryItem() override;

                Type type() const;

                void setType(Type value);

                Game::ItemObject* item();

                void setItem(Game::ItemObject* item);

                void render(bool eggTransparency = false) override;

                const Graphics::Size& size() const override;

                virtual bool opaque(const Graphics::Point &pos) override;

                void onMouseLeftDown(Event::Mouse* event);

                void onMouseDragStart(Event::Mouse* event);

                void onMouseDrag(Event::Mouse* event);

                void onMouseDragStop(Event::Mouse* event);

                void onArmorDragStop(Event::Mouse* event, std::shared_ptr<ItemsList> target, std::shared_ptr<InventoryItem> inventoryItem);

                void onHandDragStop(Event::Mouse* event, HAND hand, std::shared_ptr<ItemsList> target, std::shared_ptr<InventoryItem> inventoryItem);

                Event::MouseHandler& itemDragStopHandler();

            private:
                Game::ItemObject* _item = nullptr;

                Type _type = Type::INVENTORY;

                Type _oldType = Type::INVENTORY;

                Event::MouseHandler _itemDragStopHandler;

                Graphics::Size _inventorySize = Graphics::Size(70, 49);

                Graphics::Size _slotSize = Graphics::Size(90, 63);

                Graphics::Size _defaultSize = Graphics::Size(57, 40);
        };
    }
}
