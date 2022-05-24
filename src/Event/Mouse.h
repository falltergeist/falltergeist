#pragma once

// Project includes
#include "../Event/Event.h"
#include "../Graphics/Point.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Event
    {
        class Mouse : public Event
        {
            public:
                enum class Button
                {
                    NONE = 0,
                    LEFT,
                    RIGHT,
                    MIDDLE,
                    X1,
                    X2
                };

                enum class Type
                {
                    BUTTON_DOWN,
                    BUTTON_UP,
                    MOVE
                };

                static const char* typeToString(Type);

                Mouse(Type type);
                Mouse(const Mouse& event, const std::string& newName);
                Mouse(const Mouse& event);
                ~Mouse() override;

                /**
                 * @brief Type of an original event from OS.
                 */
                Type originalType() const;

                /**
                 * Cursor position on screen.
                 */
                const Graphics::Point& position() const;

                void setPosition(const Graphics::Point& position);

                /**
                 * @brief Which button was pressed during mouse button events.
                 */
                Button button() const;

                void setButton(Button);

                bool leftButton() const;

                bool rightButton() const;

                /**
                 * @brief Whether control key is pressed.
                 */
                bool controlPressed() const;
                void setControlPressed(bool value);

                /**
                 * @brief Whether shift key is pressed.
                 */
                bool shiftPressed() const;
                void setShiftPressed(bool value);

                /**
                 * @brief Whether alt key is pressed.
                 */
                bool altPressed() const;
                void setAltPressed(bool altPressed);

            protected:
                bool _controlPressed = false;

                bool _shiftPressed = false;

                bool _altPressed = false;

                bool _obstacle = false;

                Button _button = Button::NONE;

                Type _type;

                Graphics::Point _position;
        };
    }
}
