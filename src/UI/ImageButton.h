#pragma once

#include <string>
#include <vector>
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace Event
    {
        class Mouse;
    }
    namespace UI
    {
        class ImageButton final: public Falltergeist::UI::Base
        {
            public:
                ImageButton(
                    const Point &pos,
                    std::shared_ptr<Graphics::Sprite> buttonUpSprite,
                    std::shared_ptr<Graphics::Sprite> buttonDownSprite,
                    std::string buttonUpSoundFilename,
                    std::string buttonDownSoundFilename,
                    bool checkBoxMode
                );
                virtual ~ImageButton() = default;

                //void setState(unsigned int value);

                bool checked();
                void setChecked(bool _checked);

                bool enabled();
                void setEnabled(bool _enabled);

                virtual void handle(Event::Mouse* mouseEvent) override;
                virtual void render(bool eggTransparency = false) override;
                virtual bool opaque(const Point &pos) override;

            protected:
                bool checkboxMode = false; // remember new state after click
                bool _checked = false;
                bool _enabled = true;

                std::string buttonDownSoundFilename;
                std::string buttonUpSoundFilename;
                std::shared_ptr<Graphics::Sprite> buttonUpSprite;
                std::shared_ptr<Graphics::Sprite> buttonDownSprite;

                void _onMouseClick(Event::Mouse* event);
                void _onMouseDown(Event::Mouse* event);
                void _onMouseOut(Event::Mouse* event);
        };
    }
}
