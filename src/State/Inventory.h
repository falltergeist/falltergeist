#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace Game
    {
        class ItemObject;
    }
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }
    namespace State
    {
        class Inventory final : public State
        {
            public:
                Inventory(std::shared_ptr<UI::IResourceManager> resourceManager);
                Inventory(const Inventory&) = delete;
                Inventory& operator=(const Inventory&) = delete;
                ~Inventory() override = default;

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
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
                void _screenShow (unsigned int PID);
        };
    }
}
