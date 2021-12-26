#pragma once

#include "../Event/Event.h"
#include "../Graphics/Point.h"

namespace Falltergeist
{
    namespace Event
    {
        using Graphics::Point;

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
                const Point& position() const;
                void setPosition(const Point& position);

                /**
                 * The offset for which cursor moved relative to last event. Used for move events.
                 */
                const Point& offset() const;
                void setOffset(const Point& offset);

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

                /**
                 * Indicates that an obstacle was detected under mouse cursor during event capturing.
                 */
                bool obstacle() const;
                /**
                 * Sets obstacle flag. Used for event capturing.
                 */
                void setObstacle(bool obstacle);

            protected:
                bool _controlPressed = false;

                bool _shiftPressed = false;

                bool _altPressed = false;

                bool _obstacle = false;

                Button _button = Button::NONE;

                Type _type;

                Point _position;

                Point _offset;
        };
    }
}
