/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// Related headers
#include "../UI/ScrollableTextArea.h"

// C++ standard includes
#include <algorithm>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace UI
{

int ScrollableTextArea::lineOffset() const
{
    return _lineOffset;
}

void ScrollableTextArea::setLineOffset(int offset)
{
    _lineOffset = offset;
}

virtual std::vector<TextArea::Line> ScrollableTextArea::_generateLines()
{
    return TextArea::_generateLines();
}

}
}
