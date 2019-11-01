#include <memory>
#include "../UI/Image.h"
#include "../UI/ImageList.h"

namespace Falltergeist
{
    namespace UI
    {
        ImageList::ImageList(const Point& pos) : Falltergeist::UI::Base(pos)
        {
        }

        ImageList::ImageList(std::vector<std::string> imageList, int x, int y) : ImageList(Point(x, y))
        {
            for (auto& frmName : imageList) {
                addImage(std::make_unique<Image>(frmName));
            }
        }

        ImageList::~ImageList()
        {
        }

        unsigned int ImageList::currentImage() const
        {
            return _currentImage;
        }

        void ImageList::setCurrentImage(unsigned int number)
        {
            _currentImage = number;
        }

        void ImageList::addImage(std::unique_ptr<Image> image)
        {
            _images.push_back(std::move(image));
            _images.back()->setPosition(position());
        }

        void ImageList::addImage(const std::string& filename)
        {
            addImage(std::make_unique<Image>(filename));
        }

        const std::vector<std::unique_ptr<Image>>& ImageList::images() const
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
