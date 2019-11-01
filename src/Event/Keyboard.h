#pragma once

#include "../Event/Event.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard : public Event
        {
            public:
                enum class Type
                {
                    KEY_DOWN,
                    KEY_UP
                };

                static const char* typeToString(Type);

                Keyboard(Type type);
                Keyboard(const Keyboard& event, const std::string& newName);
                Keyboard(const Keyboard& event);
                ~Keyboard() override;

                /**
                 * @brief Type of an original event from OS.
                 */
                Type originalType() const;

                int keyCode() const;
                void setKeyCode(int value);

                bool shiftPressed() const;
                void setShiftPressed(bool value);

                bool controlPressed() const;
                void setControlPressed(bool value);

                bool altPressed() const;
                void setAltPressed(bool value);

            protected:
                bool _altPressed = false;
                bool _controlPressed = false;
                bool _shiftPressed = false;
                int _keyCode = 0;

                Type _type;
        };
    }
}
