#pragma once

#include <map>
#include <vector>
#include "../State/State.h"

namespace Falltergeist
{
    namespace UI
    {
        class BigCounter;
        class HiddenMask;
        class Image;
        class ImageButton;
        class TextArea;
    }
    namespace State
    {
        class PlayerEdit : public State
        {
            public:
                PlayerEdit();
                ~PlayerEdit() override;

                void init() override;
                void think() override;
                void render() override;

                void onMaskClick(Event::Mouse* event);
                void onButtonClick(Event::Mouse* event);
                void onAgeButtonClick(Event::Mouse* event);
                void onNameButtonClick(Event::Mouse* event);
                void onGenderButtonClick(Event::Mouse* event);
                void onLabelClick(Event::Mouse* event);
                void doCancel();
                void doDone();
                void doPrint();

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
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
        };
    }
}

