#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace State
    {
        class PipBoy : public State
        {
            public:
                PipBoy(std::shared_ptr<UI::IResourceManager> resourceManager);
                ~PipBoy() override;

                void init() override;

                void onCloseButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
        };
    }
}
