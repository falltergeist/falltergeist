#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace Game
    {
        class ItemObject;
    }
    namespace State
    {
        class Inventory : public State
        {
            public:
                Inventory();
                ~Inventory() override;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
                void onScrollUpButtonClick(Event::Mouse* event);
                void onScrollDownButtonClick(Event::Mouse* event);
                void onArmorSlotMouseDown(Event::Mouse* event);
                void onLeftHandSlotMouseDown(Event::Mouse* event);
                void onRightHandSlotMouseDown(Event::Mouse* event);
                void enableScrollDownButton(bool enable);
                void enableScrollUpButton(bool enable);
                //void onSlotMouseDown(Event::Mouse* event);
                //void onSlotMouseUp(Event::Mouse* event);
                //void onSlotDrag(Event::Mouse* event);
                void backgroundRightClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
                void onInventoryModified();

            private:
                std::string _handItemSummary (Game::ItemObject* hand);
                void _screenShow (unsigned int PID);
        };
    }
}
