/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_EXCEPTION_H
#define FALLTERGEIST_EXCEPTION_H

// C++ standard includes
#include <exception>
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{

class Exception : public std::exception
{
private:
    std::string _message;
public:
    explicit Exception(const char* message);
    explicit Exception(const std::string& message);
    virtual ~Exception() throw();
    virtual const char* what() const throw();
};

}
#endif // FALLTERGEIST_EXCEPTION_H
