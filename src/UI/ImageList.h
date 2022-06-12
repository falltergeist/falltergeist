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
        class Image;

        class ImageList : public Falltergeist::UI::Base
        {
            public:
                ImageList(const Graphics::Point& pos, const std::vector<std::shared_ptr<Image>>& imageList);

                virtual ~ImageList() = default;

                void addImage(std::shared_ptr<Image> &image);

                void setCurrentImage(unsigned int number);

                unsigned int currentImage() const;

                const std::vector<std::shared_ptr<Image>>& images() const;

                virtual bool opaque(const Graphics::Point &pos) override;

                virtual void render(bool eggTransparency) override;

                virtual void setPosition(const Graphics::Point &pos) override;

            private:
                std::vector<std::shared_ptr<Image>> _images;

                unsigned int _currentImage = 0;
        };
    }
}
