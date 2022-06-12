#pragma once

// Project includes
#include "../UI/Base.h"
#include "../UI/InventoryItem.h"

// Third-party includes

// stdlib
#include <vector>

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
        class ItemsList : public Falltergeist::UI::Base
        {
            public:
                ItemsList(const Graphics::Point& pos);

                void setItems(std::vector<Game::ItemObject*>* items);

                std::vector<Game::ItemObject*>* items();

                std::vector<std::shared_ptr<InventoryItem>>& inventoryItems();

                std::shared_ptr<InventoryItem> draggedItem();

                void update();

                void scrollUp();

                void scrollDown();

                bool canScrollUp();

                bool canScrollDown();

                unsigned int slotsNumber() const;

                void setSlotsNumber(unsigned int value);

                unsigned int slotOffset() const;
                // void setSlotOffset(unsigned int value);

                virtual void render(bool eggTransparency = false) override;

                void onMouseLeftDown(Event::Mouse* event);

                void onMouseDragStart(Event::Mouse* event);

                void onMouseDrag(Event::Mouse* event);

                void onMouseDragStop(Event::Mouse* event);

                void onItemDragStop(Event::Mouse* event, HAND hand, std::shared_ptr<UI::InventoryItem> target);

                void onItemDragStop(Event::Mouse* event, std::shared_ptr<ItemsList> target);

                void onItemDragStop(Event::Mouse* event, std::shared_ptr<UI::InventoryItem> target);

                void addItem(std::shared_ptr<InventoryItem> item, unsigned int ammount);

                void removeItem(std::shared_ptr<InventoryItem> item, unsigned int ammount);

                Event::MouseHandler& itemDragStopHandler();

                Event::Handler& itemsListModifiedHandler();

                virtual bool opaque(const Graphics::Point &pos) override;

            private:
                std::vector<Game::ItemObject*>* _items = nullptr;

                std::shared_ptr<InventoryItem> _draggedItem = nullptr;

                Graphics::Point _draggedItemInitialPosition;

                std::vector<std::shared_ptr<InventoryItem>> _inventoryItems;

                InventoryItem::Type _type = InventoryItem::Type::INVENTORY;

                unsigned int _slotsNumber = 7; // Height of widget in items

                unsigned int _slotOffset = 0;

                unsigned int _slotWidth = 77;

                unsigned int _slotHeight = 40;

                Event::MouseHandler _itemDragStopHandler;

                Event::Handler _itemsListModifiedHandler;
        };
    }
}
