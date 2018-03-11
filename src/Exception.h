/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#include <stdexcept>
#include <exception>
#include <string>

namespace Falltergeist
{
    class Exception : public std::exception
    {
        public:
            explicit Exception(const char* message);
            explicit Exception(const std::string& message);
            const char* what() const noexcept override;

        private:
            std::runtime_error _error;
    };
}

#endif // FALLTERGEIST_EXCEPTION_H
