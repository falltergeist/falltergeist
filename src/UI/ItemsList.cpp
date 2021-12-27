#include <memory>
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Rect.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../UI/InventoryItem.h"
#include "../UI/ItemsList.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace UI
    {
        using Graphics::Rect;

        ItemsList::ItemsList(const Point& pos) : Falltergeist::UI::Base(pos)
        {
            mouseDownHandler().add( std::bind(&ItemsList::onMouseLeftDown, this, std::placeholders::_1));
            mouseDragStartHandler().add(std::bind(&ItemsList::onMouseDragStart, this, std::placeholders::_1));
            mouseDragHandler().add(     std::bind(&ItemsList::onMouseDrag, this, std::placeholders::_1));
            mouseDragStopHandler().add( std::bind(&ItemsList::onMouseDragStop, this, std::placeholders::_1));
        }

        void ItemsList::setItems(std::vector<Game::ItemObject*>* items)
        {
            _items = items;
            update();
        }

        std::vector<Game::ItemObject*>* ItemsList::items()
        {
            return _items;
        }

        void ItemsList::update()
        {
            _inventoryItems.clear();

            for (unsigned int i = _slotOffset; i < items()->size() && i != _slotOffset + _slotsNumber; i++) {
                _inventoryItems.push_back(std::unique_ptr<InventoryItem>(new InventoryItem(items()->at(i))));
            }
        }

        void ItemsList::render(bool eggTransparency)
        {
            unsigned int i = 0;
            for (auto& item : _inventoryItems) {
                Point pos = position() + Point(0, _slotHeight*i);
                item->setPosition(pos);
                item->render();

                auto itemObj = item->item();
                if (itemObj->amount() > 1) {
                    itemObj->inventoryAmountUi()->setPosition(pos + Point(9, 8));
                    itemObj->inventoryAmountUi()->render();
                }
                i++;
            }
        }

        std::vector<std::unique_ptr<InventoryItem>>& ItemsList::inventoryItems()
        {
            return _inventoryItems;
        }

        void ItemsList::onMouseLeftDown(Event::Mouse* event)
        {
        }

        void ItemsList::onMouseDragStart(Event::Mouse* event)
        {
            unsigned int index = (event->position().y() - y())/_slotHeight;
            if (index < _inventoryItems.size()) {
                Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::NONE);
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/ipickup1.acm");
                _draggedItem = _inventoryItems.at(index).get();
                _draggedItem->setType(InventoryItem::Type::DRAG);
                _draggedItem->setOffset((event->position() - _draggedItem->position()) - (_draggedItem->size() / 2));
            } else {
                _draggedItem = nullptr;
            }
        }

        void ItemsList::onMouseDrag(Event::Mouse* event)
        {
            if (_draggedItem) {
                _draggedItem->setOffset(event->position() - _draggedItem->rawPosition() - (_draggedItem->size() / 2.f));
            }
        }

        void ItemsList::onMouseDragStop(Event::Mouse* event)
        {
            if (_draggedItem) {
                Game::Game::getInstance()->mouse()->popState();
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/iputdown.acm");
                _draggedItem->setOffset(0, 0);
                _draggedItem->setType(_type);
                auto itemevent = std::make_unique<Event::Mouse>(*event, "itemdragstop");
                emitEvent(std::move(itemevent), itemDragStopHandler());
            }
        }

        void ItemsList::onItemDragStop(Event::Mouse* event, ItemsList* target)
        {
            // check if mouse is in this item list
            if (!Rect::inRect(event->position(), position(), Size(_slotWidth, _slotHeight*_slotsNumber))) {
                return;
            }

            // @todo create addItem method
            addItem(target->draggedItem(), 1);
            target->removeItem(target->draggedItem(), 1);
            target->update();
        }

        void ItemsList::onItemDragStop(Event::Mouse* event, UI::InventoryItem* target)
        {
            // check if mouse is in this item list
            if (!Rect::inRect(event->position(), position(), Size(_slotWidth, _slotHeight*_slotsNumber))) {
                return;
            }

            // @todo create addItem method
            addItem(target, 1);
            if (dynamic_cast<Game::ArmorItemObject*>(target->item()) && target->type() == InventoryItem::Type::SLOT) {
                Game::Game::getInstance()->player()->setArmorSlot(nullptr);
            }
            target->setItem(0);
        }

        void ItemsList::onItemDragStop(Event::Mouse* event, HAND hand, UI::InventoryItem* target)
        {
            // check if mouse is in this item list
            if (Rect::inRect(event->position(), position(), Size(_slotWidth, _slotHeight*_slotsNumber))) {
                addItem(target, 1);
                if (hand == HAND::LEFT) {
                    Game::Game::getInstance()->player()->setLeftHandSlot(nullptr);
                } else {
                    Game::Game::getInstance()->player()->setRightHandSlot(nullptr);
                }
                target->setItem(0);
            }
        }

        InventoryItem* ItemsList::draggedItem()
        {
            return _draggedItem;
        }

        void ItemsList::addItem(InventoryItem* item, unsigned int amount)
        {
            _items->push_back(item->item());
            this->update();
            emitEvent(std::make_unique<Event::Event>("itemsListModified"), itemsListModifiedHandler());
        }

        void ItemsList::removeItem(InventoryItem* item, unsigned int amount)
        {
            for (auto it = _items->begin(); it != _items->end(); ++it) {
                Game::ItemObject* object = *it;
                if (object == item->item()) {
                    _items->erase(it);
                    break;
                }
            }
            this->update();
            emitEvent(std::make_unique<Event::Event>("itemsListModified"), itemsListModifiedHandler());
        }

        bool ItemsList::canScrollUp()
        {
            return _slotOffset > 0;
        }

        bool ItemsList::canScrollDown()
        {
            return _slotOffset + _slotsNumber < _items->size();
        }

        void ItemsList::scrollUp()
        {
            _slotOffset--;
            this->update();
        }

        void ItemsList::scrollDown()
        {
            _slotOffset++;
            this->update();
        }

        unsigned int ItemsList::slotsNumber() const
        {
            return _slotsNumber;
        }

        void ItemsList::setSlotsNumber(unsigned int value)
        {
            _slotsNumber = value;
        }

        unsigned int ItemsList::slotOffset() const
        {
            return _slotOffset;
        }

        Event::MouseHandler& ItemsList::itemDragStopHandler()
        {
            return _itemDragStopHandler;
        }

        Event::Handler& ItemsList::itemsListModifiedHandler()
        {
            return _itemsListModifiedHandler;
        }

        bool ItemsList::opaque(const Point &pos) {
            unsigned int i = 0;
            for (auto& item : _inventoryItems) {
                bool pixel = item->opaque(pos - Point(0, _slotHeight*i));
                if (pixel) {
                    return pixel;
                }
                i++;
            }
            return false;
        }
    }
}
