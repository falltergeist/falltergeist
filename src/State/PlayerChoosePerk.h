#pragma once

#include <functional>
#include <vector>

#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
        class Image;
        class Rectangle;
        class TextArea;
        class TextAreaList;
    }
    namespace State
    {
        class PlayerChoosePerk : public State
        {
            public:
                PlayerChoosePerk(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~PlayerChoosePerk() = default;

                void init() override;
                void render() override;

                void selectPerk(int index);

                void onDoneButtonClick(Event::Mouse* event);
                void onCancelButtonClick(Event::Mouse* event);

            protected:

                UI::TextAreaList *_perkNames = nullptr;
                UI::TextAreaList *_perkRanks = nullptr;

                Point _bgPos;

                int _selectedIndex = 0;
                PERK _selectedPerk;
                std::vector<PERK> _perksList;
                std::vector<std::shared_ptr<UI::Image>> _images;

                // Selected perk
                UI::TextArea* _title = nullptr;
                UI::TextArea* _description = nullptr;
                std::shared_ptr<UI::Image> _selectedImage = nullptr;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
