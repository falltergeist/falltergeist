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

// Related headers
#include "../Event/Event.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        /**
         * @brief Constructor
         * @param[in] name Event name
         */
        Event::Event(const std::string& name)
        {
            _name = name;
        }

        /**
         * @brief Destructor
         */
        Event::~Event()
        {
        }

        /**
         * @brief Returns event name
         * @return Event name
         */
        std::string Event::name() const
        {
            return _name;
        }

        /**
         * @brief Sets event name
         * @param[in] name Event name
         */
        void Event::setName(const std::string& name)
        {
            _name = name;
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
