#pragma once

#include <string>
#include <vector>
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"
#include "../UI/ImageList.h"

namespace Falltergeist
{
    namespace Event
    {
        class Mouse;
    }
    namespace UI
    {
        class ImageList;
        class Image;

        class MultistateImageButton final : public UI::Base
        {
            public:
                enum class Mode
                {
                    PROGRESSION = 1,
                    CYCLIC
                };

                enum class Type
                {
                    BIG_SWITCH = 1,
                    SMALL_SWITCH
                };

                MultistateImageButton(Type type, const Point& pos);

                virtual ~MultistateImageButton() = default;

                unsigned int state() const;

                void setState(unsigned int state);

                unsigned int minState() const;

                void setMinState(unsigned int value);

                unsigned int maxState() const;

                void setMaxState(unsigned int value);

                Mode mode() const;

                void setMode(Mode mode);

                int modeFactor() const;

                void setModeFactor(int factor);

                void handle(Event::Mouse* mouseEvent) override;

                bool opaque(const Point &pos) override;

                void render(bool eggTransparency) override;

                const Size& size() const override;

            private:
                std::shared_ptr<Graphics::Sprite> _sprite;

                std::vector<Graphics::Rectangle> _rects;

                unsigned int _currentState = 0;

                Mode _mode = Mode::CYCLIC;

                Size _size;

                int _modeFactor = 1; // or -1

                unsigned int _maxState = 0;

                unsigned int _minState = 0;

                std::string _downSound;

                std::string _upSound;

                void _onMouseClick(Event::Mouse* event);

                void _onMouseUp(Event::Mouse* event);
        };
    }
}

