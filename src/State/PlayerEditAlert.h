#pragma once

#include <string>
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace State
    {
        class PlayerEditAlert final : public State
        {
            public:
                PlayerEditAlert(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~PlayerEditAlert() = default;

                void setMessage(const std::string& message);

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);

            protected:
                std::string _message;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
        };
    }
}
