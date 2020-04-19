#pragma once

#include <map>
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
                PlayerCreate(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~PlayerCreate() = default;

                void init() override;
                void think(const float &deltaTime) override;
                void render() override;

                void onMaskClick(Event::Mouse* event);
                void onButtonClick(Event::Mouse* event);
                void onAgeButtonClick(Event::Mouse* event);
                void onNameButtonClick(Event::Mouse* event);
                void onGenderButtonClick(Event::Mouse* event);
                void onLabelClick(Event::Mouse* event);
                void onBackButtonClick(Event::Mouse* event);
                void onDoneButtonClick(Event::Mouse* event);
                void onOptionsButtonClick(Event::Mouse* event);
                void doAge();
                void doName();
                void doGender();
                void doOptions();
                void doDone();
                void doBack();
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                std::shared_ptr<UI::TextArea> _selectedLabel = nullptr;
                std::shared_ptr<UI::TextArea> _title = nullptr;
                std::shared_ptr<UI::TextArea> _description = nullptr;
                std::shared_ptr<UI::Image> _selectedImage = nullptr;

                std::map<std::string, std::shared_ptr<UI::TextArea>> _labels;
                std::map<std::string, std::shared_ptr<UI::BigCounter>> _counters;
                std::map<std::string, std::shared_ptr<UI::ImageButton>> _buttons;
                std::map<std::string, std::shared_ptr<UI::HiddenMask>> _masks;
                std::map<std::string, std::string> _titles;
                std::map<std::string, std::string> _descriptions;
                std::map<std::string, std::shared_ptr<UI::Image>> _images;

                std::shared_ptr<UI::TextArea> _addLabel(const std::string& name, std::shared_ptr<UI::TextArea> label);
                std::shared_ptr<UI::ImageButton> _addButton(const std::string& name, std::shared_ptr<UI::ImageButton> button);
                std::shared_ptr<UI::BigCounter> _addCounter(const std::string& name, std::shared_ptr<UI::BigCounter> counter);
                std::shared_ptr<UI::HiddenMask> _addMask(const std::string& name, std::shared_ptr<UI::HiddenMask> mask);
                void _addTitle(const std::string& name, std::string title);
                void _addDescription(const std::string& name, std::string description);
                void _addImage(const std::string& name, std::shared_ptr<UI::Image> image);

                bool _statIncrease(unsigned int num);
                bool _statDecrease(unsigned int num);
                bool _traitToggle(unsigned int num);
                bool _skillToggle(unsigned int num);

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
