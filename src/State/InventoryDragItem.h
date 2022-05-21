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
        class InventoryDragItem final : public State
        {
            public:
                InventoryDragItem(
                    std::shared_ptr<Input::Mouse> mouse,
                    UI::ImageList* itemUi
                );

                ~InventoryDragItem() override;

                void init() override;

                void handle(Event::Event* event) override;

            private:
                UI::ImageList* _itemUi = nullptr;
        };
    }
}
