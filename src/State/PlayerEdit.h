#pragma once

// Project includes
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
        class PlayerEdit final : public State
        {
            public:
                PlayerEdit(std::shared_ptr<UI::IResourceManager> resourceManager);

                virtual ~PlayerEdit() = default;

                void init() override;

                void think(const float &deltaTime) override;

                void render() override;

                void onMaskClick(std::shared_ptr<UI::HiddenMask> target);

                void onLabelClick(std::shared_ptr<UI::TextArea> target);

                void onTabClick(Event::Mouse* event);

                void doCancel();

                void doDone();

                void doPrint();

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

                void onKeyDown(Event::Keyboard* event) override;

            private:
                void _onButtonClick(std::shared_ptr<UI::ImageButton> target);

                std::shared_ptr<UI::TextArea> _addLabel(const std::string& name, std::shared_ptr<UI::TextArea> label);

                std::shared_ptr<UI::ImageButton> _addButton(const std::string& name, std::shared_ptr<UI::ImageButton> button);

                std::shared_ptr<UI::BigCounter> _addCounter(const std::string& name, std::shared_ptr<UI::BigCounter> counter);

                std::shared_ptr<UI::HiddenMask> _addMask(const std::string& name, std::shared_ptr<UI::HiddenMask> mask);

                void _addTitle(const std::string& name, std::string title);

                void _addDescription(const std::string& name, std::string description);

                void _addImage(const std::string& name, std::shared_ptr<UI::Image> image);

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

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

        };
    }
}

