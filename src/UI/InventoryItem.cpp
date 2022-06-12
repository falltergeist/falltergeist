// Project includes
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

// Third-party includes

// stdlib
#include <memory>
#include <cmath>

namespace Falltergeist
{
    namespace UI
    {
        using Rect = Graphics::Rect;
        using Size = Graphics::Size;

        InventoryItem::InventoryItem(Game::ItemObject *item, const Graphics::Point& pos) : Falltergeist::UI::Base(pos)
        {
            _item = item;
            mouseDownHandler().add(std::bind(&InventoryItem::onMouseLeftDown, this, std::placeholders::_1));
            mouseDragStartHandler().add(std::bind(&InventoryItem::onMouseDragStart, this, std::placeholders::_1));
            mouseDragHandler().add(std::bind(&InventoryItem::onMouseDrag, this, std::placeholders::_1));
            mouseDragStopHandler().add(std::bind(&InventoryItem::onMouseDragStop, this, std::placeholders::_1));
        }

        InventoryItem::~InventoryItem()
        {
        }

        InventoryItem::Type InventoryItem::type() const
        {
            return _type;
        }

        void InventoryItem::setType(Type value)
        {
            _type = value;
        }

        void InventoryItem::render(bool eggTransparency)
        {
            if (!_item) {
                return;
            }

            double widthRatio = 0.0;
            double heightRatio = 0.0;
            unsigned int newWidth = 0;
            unsigned int newHeight = 0;
            Size texSize;

            auto slotUi = _item->inventorySlotUi();
            auto dragUi = _item->inventoryDragUi();
            auto inventoryUi = _item->inventoryUi();

            switch (_type)
            {
                case Type::SLOT:
                    widthRatio = static_cast<double>(88) / static_cast<double>(slotUi->size().width());
                    heightRatio = static_cast<double>(58) / static_cast<double>(slotUi->size().height());

                    newWidth = static_cast<unsigned int>(static_cast<double>(slotUi->size().width()) * static_cast<double>(heightRatio));

                    if (newWidth <= 88) {
                        texSize = Size(newWidth, 58);
                        slotUi->setPosition(position() + (this->size() - texSize) / 2);
                        slotUi->render(Size(newWidth, 58), false);
                        return;
                    }
                    newHeight = static_cast<unsigned int>(static_cast<double>(slotUi->size().height()) * static_cast<double>(widthRatio));
                    texSize = Size(88, newHeight);
                    slotUi->setPosition(position() + (this->size() - texSize) / 2);
                    slotUi->render(Size(88, newHeight), false);
                    break;
                case Type::DRAG:
                    dragUi->setPosition(position() + offset());
                    dragUi->render();
                    break;
                default:
                    inventoryUi->setPosition(position());

                    widthRatio = static_cast<double>(_defaultSize.width()) / static_cast<double>(inventoryUi->size().width());
                    heightRatio = static_cast<double>(_defaultSize.height()) / static_cast<double>(inventoryUi->size().height());

                    newWidth = static_cast<unsigned int>(static_cast<double>(inventoryUi->size().width()) * static_cast<double>(heightRatio));

                    if (newWidth <= _defaultSize.width()) {
                        texSize = Size(newWidth, _defaultSize.height());
                        inventoryUi->setPosition(position() + (this->size() - texSize) / 2);

                        inventoryUi->render(Size(newWidth, _defaultSize.height()), false);
                        return;
                    }
                    newHeight = static_cast<unsigned int>(static_cast<double>(inventoryUi->size().height()) * static_cast<double>(widthRatio));
                    texSize = Size(_defaultSize.width(), newHeight);
                    inventoryUi->setPosition(position() + (this->size() - texSize) / 2);
                    inventoryUi->render(Size(_defaultSize.width(), newHeight), false);
                    break;
            }
        }

        Game::ItemObject* InventoryItem::item()
        {
            return _item;
        }

        void InventoryItem::setItem(Game::ItemObject* item)
        {
            _item = item;
        }

        void InventoryItem::onMouseLeftDown(Event::Mouse* event)
        {
        }

        void InventoryItem::onMouseDragStart(Event::Mouse* event)
        {
            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::NONE);
            Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/ipickup1.acm");
            _oldType = type();
            setType(Type::DRAG);
            setOffset((event->position() - _position) - size() / 2);
        }

        void InventoryItem::onMouseDrag(Event::Mouse* event)
        {
            setOffset((event->position() - position()) - (size() / 2.f));
        }

        void InventoryItem::onMouseDragStop(Event::Mouse* event)
        {
            Game::Game::getInstance()->mouse()->popState();
            Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/iputdown.acm");
            setOffset({0, 0});
            setType(_oldType);

            auto itemevent = std::make_unique<Event::Mouse>(*event, "itemdragstop");
            itemevent->setPosition(event->position());
            emitEvent(std::move(itemevent), itemDragStopHandler());
        }

        void InventoryItem::onArmorDragStop(Event::Mouse* event, std::shared_ptr<ItemsList> target)
        {
            // Check if mouse is over this item
            if (!Rect::inRect(event->position(), position(), size())) {
                return;
            }

            auto draggedItem = target->draggedItem();
            auto itemObject = draggedItem->item();
            if (itemObject->subtype() != Game::ItemObject::Subtype::ARMOR) {
                return;
            }
            target->removeItem(draggedItem, 1);
            // place current armor back to inventory
            if (_item) {
                // TODO fix me
                //target->addItem(this, 1);
            }
            this->setItem(itemObject);
            if (auto armor = dynamic_cast<Game::ArmorItemObject*>(itemObject)) {
                Game::Game::getInstance()->player()->setArmorSlot(armor);
            }
        }

        void InventoryItem::onHandDragStop(Event::Mouse* event, HAND hand, std::shared_ptr<ItemsList> target)
        {
            // Check if mouse is over this item
            if (!Rect::inRect(event->position(), position(), size()))
            {
                return;
            }

            auto itemUi = target->draggedItem();
            auto item = itemUi->item();
            target->removeItem(itemUi, 1);
            // place current weapon back to inventory
            if (_item) {
                // TODO fix me
                //target->addItem(this, 1);
            }
            this->setItem(item);
            auto player = Game::Game::getInstance()->player();
            if (hand == HAND::LEFT) {
                player->setLeftHandSlot(item);
            } else {
                player->setRightHandSlot(item);
            }
        }

        const Graphics::Size& InventoryItem::size() const
        {
            switch (_type)
            {
                case Type::INVENTORY:
                    return _inventorySize;
                case Type::SLOT:
                    return _slotSize;
                default:
                    return _defaultSize;
            }
        }

        Event::MouseHandler& InventoryItem::itemDragStopHandler()
        {
            return _itemDragStopHandler;
        }

        bool InventoryItem::opaque(const Graphics::Point &pos)
        {
            if (!_item) {
                return false;
            }
            return Rect::inRect(pos, this->size());
        }
    }
}
