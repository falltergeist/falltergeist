#pragma once

#include "../Graphics/Sprite.h"
#include "../UI/Base.h"
#include <string>
#include <vector>

namespace Falltergeist {
    namespace Event {
        class Mouse;
    }
    namespace UI {
        class ImageButton final : public Falltergeist::UI::Base {
        public:
            ImageButton(const Graphics::Point& pos, std::shared_ptr<Graphics::Sprite> buttonUpSprite, std::shared_ptr<Graphics::Sprite> buttonDownSprite,
                        std::string buttonUpSoundFilename, std::string buttonDownSoundFilename, bool checkBoxMode);

            virtual ~ImageButton() = default;

            bool checked();

            void setChecked(bool checked);

            bool enabled();

            void setEnabled(bool enabled);

            virtual void handle(Event::Mouse* mouseEvent) override;

            virtual void render(bool eggTransparency = false) override;

            virtual bool opaque(const Graphics::Point& pos) override;

        protected:
            bool _checkboxMode = false; // remember new state after click

            bool _checked = false;

            bool _enabled = true;

            std::string _buttonDownSoundFilename;

            std::string _buttonUpSoundFilename;

            std::shared_ptr<Graphics::Sprite> _buttonUpSprite;

            std::shared_ptr<Graphics::Sprite> _buttonDownSprite;

            void _onMouseClick();

            void _onMouseDown(Event::Mouse* event);
        };
    }
}
