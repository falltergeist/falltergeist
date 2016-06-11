/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist Developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FALLTERGEIST_EVENT_EVENT_H
#define FALLTERGEIST_EVENT_EVENT_H

// C++ standard includes
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class EventTarget;

        /**
         * @brief Base event class
         *
         * This class is base for all other event classes
         */
        class Event
        {
            public:
                Event(const std::string& name);
                virtual ~Event();

                std::string name() const;
                void setName(const std::string& name);

                EventTarget* target() const;
                void setTarget(EventTarget* value);

                bool handled() const;
                /**
                 * @brief Sets that event is handled or not.
                 * If called from within handle(Event*) function, affects event capturing process by preventing OS Event to "fall down" to other elements.
                 * If called from within the event handler function, prevents other handlers of the same event to be called.
                 * @param value the handled flag.
                 */
                void setHandled(bool value = true);

            protected:
                /// Is event handled or not
                bool _handled = false;
                /// Event name
                std::string _name;
                /// Event target
                EventTarget* _target = nullptr;
        };
    }
}
#endif // FALLTERGEIST_EVENT_EVENT_H
