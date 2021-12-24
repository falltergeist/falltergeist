#include "../Event/Event.h"

namespace Falltergeist
{
    namespace Event
    {
        Event::Event(const std::string& name) : _name(name) {
        }

        const std::string& Event::name() const
        {
            return _name;
        }

        /**
         * @brief Returns event target
         * @return Event target
         */
        EventTarget* Event::target() const
        {
            return _target;
        }

        /**
         * @brief Sets event target
         * @param[in] value Event target
         */
        void Event::setTarget(EventTarget* value)
        {
            _target = value;
        }

        /**
         * @brief Returns if event is handled or not.
         * @return Is event handled or not
         */
        bool Event::handled() const
        {
            return _handled;
        }

        void Event::setHandled(bool value)
        {
            _handled = value;
        }
    }
}
