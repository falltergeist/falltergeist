/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// Related headers
#include "../UI/InventoryItem.h"

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/ItemObject.h"
#include "../Graphics/Point.h"
#include "../Graphics/Rect.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../UI/Image.h"
#include "../UI/ItemsList.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
using Graphics::Rect;

InventoryItem::InventoryItem(Game::ItemObject *item, const Point& pos) : Falltergeist::UI::Base(pos)
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
/*
Graphics::Texture* InventoryItem::texture() const
{
    //if (!_texture)
    //{
    //    _texture = new Texture(this->width(), this->height());
    //    _texture->fill(0x000000ff);
    //}
    //return _texture;

    if (!_item) return 0;

    switch (_type)
    {
        case Type::SLOT:
            return _item->inventorySlotUi()->texture();
        case Type::DRAG:
            return _item->inventoryDragUi()->texture();
        default: {}
    }

    return _item->inventoryUi()->texture();
}
*/
void InventoryItem::render(bool eggTransparency)
{
    //return ActiveUI::render();
    if (!_item) return;

    double widthRatio;
    double heightRatio;
    unsigned int newWidth;
    unsigned int newHeight;
    Size texSize;

    auto slotUi = _item->inventorySlotUi();
    auto dragUi = _item->inventoryDragUi();
    auto inventoryUi = _item->inventoryUi();

    switch (_type)
    {
        case Type::SLOT:
            widthRatio = static_cast<double>(88) / static_cast<double>(slotUi->width());
            heightRatio = static_cast<double>(58) / static_cast<double>(slotUi->height());

            newWidth = static_cast<unsigned int>(static_cast<double>(slotUi->width()) * static_cast<double>(heightRatio));

            if (newWidth <= 88)
            {
                texSize = Size(newWidth, 58);
                slotUi->setPosition(position() + (this->size() - texSize) / 2);
                slotUi->render(Size(newWidth, 58), false);
                return;
            }
            newHeight = static_cast<unsigned int>(static_cast<double>(slotUi->height()) * static_cast<double>(widthRatio));
            texSize = Size(88, newHeight);
            slotUi->setPosition(position() + (this->size() - texSize) / 2);
            slotUi->render(Size(88, newHeight), false);
            break;
        case Type::DRAG:
            dragUi->setPosition(position());
            dragUi->render();
            break;
        default:
            inventoryUi->setPosition(position());

            widthRatio = static_cast<double>(57) / static_cast<double>(inventoryUi->width());
            heightRatio = static_cast<double>(40) / static_cast<double>(inventoryUi->height());

            newWidth = static_cast<unsigned int>(static_cast<double>(inventoryUi->width()) * static_cast<double>(heightRatio));

            if (newWidth <= 57)
            {
                texSize = Size(newWidth, 40);
                inventoryUi->setPosition(position() + (this->size() - texSize) / 2);

                inventoryUi->render(Size(newWidth, 40), false);
                return;
            }
            newHeight = static_cast<unsigned int>(static_cast<double>(inventoryUi->height()) * static_cast<double>(widthRatio));
            texSize = Size(57, newHeight);
            inventoryUi->setPosition(position() + (this->size() - texSize) / 2);
            inventoryUi->render(Size(57, newHeight), false);
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
    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::NONE);
    Game::getInstance()->mixer()->playACMSound("sound/sfx/ipickup1.acm");
    _oldType = type();
    setType(Type::DRAG);
    setOffset((event->position() - _position) - size() / 2);
}

void InventoryItem::onMouseDrag(Event::Mouse* event)
{
    setOffset(offset() + event->offset());
}

void InventoryItem::onMouseDragStop(Event::Mouse* event)
{
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->mixer()->playACMSound("sound/sfx/iputdown.acm");
    setOffset({0, 0});
    setType(_oldType);

    auto itemevent = std::make_unique<Event::Mouse>(*event, "itemdragstop");
    itemevent->setPosition(event->position());
    itemevent->setTarget(this);
    emitEvent(std::move(itemevent), itemDragStopHandler());
}

void InventoryItem::onArmorDragStop(Event::Mouse* event)
{
    // Check if mouse is over this item
    if (!Rect::inRect(event->position(), position(), size()))
    {
        return;
    }

    if (ItemsList* itemsList = dynamic_cast<ItemsList*>(event->target()))
    {

        InventoryItem* draggedItem = itemsList->draggedItem();
        auto itemObject = draggedItem->item();
        if(itemObject->subtype() != Game::ItemObject::Subtype::ARMOR) return;
        itemsList->removeItem(draggedItem, 1);
        // place current armor back to inventory
        if (_item)
        {
            itemsList->addItem(this, 1);
        }
        this->setItem(itemObject);
        if (auto armor = dynamic_cast<Game::ArmorItemObject*>(itemObject))
        {
            Game::getInstance()->player()->setArmorSlot(armor);
        }
    }
}

void InventoryItem::onHandDragStop(Event::Mouse* event, HAND hand)
{
    // Check if mouse is over this item
    if (!Rect::inRect(event->position(), position(), size()))
    {
        return;
    }

    if (ItemsList* itemsList = dynamic_cast<ItemsList*>(event->target()))
    {
        InventoryItem* itemUi = itemsList->draggedItem();
        auto item = itemUi->item();
        itemsList->removeItem(itemUi, 1);
        // place current weapon back to inventory
        if (_item)
        {
            itemsList->addItem(this, 1);
        }
        this->setItem(item);
        auto player = Game::getInstance()->player();
        if (hand == HAND::LEFT)
        {
            player->setLeftHandSlot(item);
        }
        else
        {
            player->setRightHandSlot(item);
        }
    }
}

Size InventoryItem::size() const
{
    switch (_type)
    {
        case Type::INVENTORY:
            return Size(70, 49);
        case Type::SLOT:
            return Size(90, 63);
        default:
            return Size(57, 40);
    }
}

Event::MouseHandler& InventoryItem::itemDragStopHandler()
{
    return _itemDragStopHandler;
}

bool InventoryItem::opaque(const Point &pos) {
    if (!_item) return false;
    return Rect::inRect(pos, this->size());
}
}
}
