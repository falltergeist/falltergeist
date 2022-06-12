#pragma once

// Project includes
#include "../State/State.h"

// Third-party includes

// stdlib

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
                InventoryDragItem(std::shared_ptr<UI::ImageList>& itemUi);

                ~InventoryDragItem() override;

                void init() override;

                void handle(Event::Event* event) override;

            private:
                std::shared_ptr<UI::ImageList> _itemUi = nullptr;
        };
    }
}
