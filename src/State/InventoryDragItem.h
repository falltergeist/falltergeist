#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace UI
    {
        class ImageList;
    }
    namespace State
    {
        class InventoryDragItem : public State
        {
            public:
                InventoryDragItem(UI::ImageList* itemUi);
                ~InventoryDragItem() override;

                void init() override;
                void handle(Event::Event* event) override;

            protected:
                UI::ImageList* _itemUi = nullptr;
        };
    }
}
