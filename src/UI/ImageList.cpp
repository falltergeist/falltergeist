// Project includes
#include "../UI/Image.h"
#include "../UI/ImageList.h"

// Third-party includes

// stdlib
#include <memory>

namespace Falltergeist
{
    namespace UI
    {
        ImageList::ImageList(const Graphics::Point& pos, const std::vector<Image*> &imageList) : Falltergeist::UI::Base(pos)
        {
            for (auto& image : imageList) {
                auto imagePtr = std::unique_ptr<Image>(image);
                addImage(imagePtr);
            }
        }

        unsigned int ImageList::currentImage() const
        {
            return _currentImage;
        }

        void ImageList::setCurrentImage(unsigned int number)
        {
            _currentImage = number;
        }

        void ImageList::addImage(std::unique_ptr<Image> &image)
        {
            _images.push_back(std::move(image));
            _images.back()->setPosition(position());
        }

        const std::vector<std::unique_ptr<Image>>& ImageList::images() const
        {
            return _images;
        }

        void ImageList::render(bool eggTransparency)
        {
            _images.at(currentImage())->render(eggTransparency);
        }

        bool ImageList::opaque(const Graphics::Point &pos)
        {
            return _images.at(currentImage())->opaque(pos);
        }

        void ImageList::setPosition(const Graphics::Point &pos)
        {
            Base::setPosition(pos);
            for (auto& image: _images) {
                image->setPosition(position());
            }
        }
    }
}
