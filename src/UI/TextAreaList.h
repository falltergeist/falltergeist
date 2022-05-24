#pragma once

// Project includes
#include "../UI/Base.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace UI
    {
        class TextArea;

        class TextAreaList : public Falltergeist::UI::Base
        {
            public:
                TextAreaList(const Graphics::Point& pos = Graphics::Point());

                ~TextAreaList() override;

                void addArea(std::unique_ptr<TextArea> area);

                const std::vector<std::unique_ptr<TextArea>>& textAreas() const;

                void scrollDown(int count = 1);

                void scrollUp(int count = 1);

                void scrollTo(int index);

                bool opaque(const Graphics::Point &pos) override;

                void render(bool eggTransparency) override;

                void setSize(Graphics::Size size);

            private:
                Graphics::Size _size;

                std::vector<std::unique_ptr<TextArea>> _areas;

                int _areaIndex = 0;

                unsigned int _visibleCount = 0;

                int _totalHeight = 0;

                void _recalculatePositions();
        };
    }
}
