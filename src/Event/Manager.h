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

#ifndef FALLTERGEIST_EVENT_MANAGER_H
#define FALLTERGEIST_EVENT_MANAGER_H

// C++ standard includes

// Falltergeist includes
#include "../Base/Singleton.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{

/**
 * @brief The Event Manager class
 *
 * This is main event dispatcher class
 */
class Manager
{
public:
    static Manager* getInstance();

private:
    friend class Base::Singleton<Manager>;

    Manager();
    ~Manager();

    /// Copy constructor
    Manager(Manager const&) = delete;
    /// Assignment
    void operator=(Manager const&) = delete;
};

}
}
#endif // FALLTERGEIST_EVENT_MANAGER_H
