#pragma once

// Project includes
#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib
#include <map>
#include <vector>

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
        class BigCounter;
        class HiddenMask;
        class Image;
        class ImageButton;
        class TextArea;
    }
    namespace State
    {
        class PlayerCreate final : public State
        {
            public:
                PlayerCreate(std::shared_ptr<UI::IResourceManager> resourceManager, std::shared_ptr<ILogger> logger);
                virtual ~PlayerCreate() = default;

                void init() override;
                void think(const float &deltaTime) override;
                void render() override;

                void onMaskClick(UI::HiddenMask* target);

                void onLabelClick(UI::TextArea* target);

                void onKeyDown(Event::Keyboard* event) override;

            protected:
                UI::TextArea* _selectedLabel = nullptr;
                UI::TextArea* _title = nullptr;
                UI::TextArea* _description = nullptr;
                UI::Image* _selectedImage = nullptr;

                std::map<std::string, UI::TextArea*> _labels;
                std::map<std::string, UI::BigCounter*> _counters;
                std::map<std::string, UI::ImageButton*> _buttons;
                std::map<std::string, UI::HiddenMask*> _masks;
                std::map<std::string, std::string> _titles;
                std::map<std::string, std::string> _descriptions;
                std::map<std::string, UI::Image*> _images;

                UI::TextArea* _addLabel(const std::string& name, UI::TextArea* label);
                UI::ImageButton* _addButton(const std::string& name, UI::ImageButton* button);
                UI::BigCounter* _addCounter(const std::string& name, UI::BigCounter* counter);
                UI::HiddenMask* _addMask(const std::string& name, UI::HiddenMask* mask);
                void _addTitle(const std::string& name, std::string title);
                void _addDescription(const std::string& name, std::string description);
                void _addImage(const std::string& name, UI::Image* image);

                bool _statIncrease(unsigned int num);
                bool _statDecrease(unsigned int num);
                bool _traitToggle(unsigned int num);
                bool _skillToggle(unsigned int num);

            private:
                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

                void _onButtonClick(UI::ImageButton* target);

                void _doAge();

                void _doName();

                void _doGender();

                void _doOptions();

                void _doDone();

                void _doBack();

        };
    }
}
