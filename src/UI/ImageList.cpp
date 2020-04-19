#include <memory>
#include "../UI/Image.h"
#include "../UI/ImageList.h"

namespace Falltergeist
{
    namespace UI
    {
        ImageList::ImageList(Point pos, std::vector<std::shared_ptr<Image>> imageList) :
            Falltergeist::UI::Base{pos},
            _images{std::move(imageList)}
        {
            for (auto& image : _images) {
                image->setPosition(position());
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

        const std::vector<std::shared_ptr<Image>>& ImageList::images() const
        {
            return _images;
        }

        void ImageList::render(bool eggTransparency)
        {
            _images.at(currentImage())->render(eggTransparency);
        }

        bool ImageList::opaque(const Point &pos)
        {
            return _images.at(currentImage())->opaque(pos);
        }

        void ImageList::setPosition(const Point &pos)
        {
            Base::setPosition(pos);
            for (auto& image: _images) {
                image->setPosition(position());
            }
        }
    }
}
