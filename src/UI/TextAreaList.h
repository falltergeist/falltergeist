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

#ifndef FALLTERGEIST_UI_TEXTAREALIST_H
#define FALLTERGEIST_UI_TEXTAREALIST_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
class TextArea;

class TextAreaList : public Falltergeist::UI::Base {
public:
    TextAreaList(const Point& pos = Point());
    ~TextAreaList() override;

    void addArea(std::unique_ptr<TextArea> area);
    const std::vector<std::unique_ptr<TextArea>>& textAreas() const;
    void scrollDown(int count = 1);
    void scrollUp(int count = 1);
    void scrollTo(int index);

    virtual bool opaque(const Point &pos) override;

    virtual void render(bool eggTransparency) override;

    void  setSize(Size size);

protected:
    Size _size;
    std::vector<std::unique_ptr<TextArea>> _areas;
    int _areaIndex = 0;
    unsigned int _visibleCount = 0;
    int _totalHeight = 0;
    void _recalculatePositions();
};

}
}


#endif //FALLTERGEIST_UI_TEXTAREALIST_H
