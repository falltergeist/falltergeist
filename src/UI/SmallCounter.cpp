// Project includes
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"
#include "../UI/SmallCounter.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        using Point = Graphics::Point;
        using Size = Graphics::Size;

        SmallCounter::SmallCounter(const Graphics::Point& pos) : Falltergeist::UI::Base(pos)
        {
            _sprite = std::make_shared<Graphics::Sprite>("art/intrface/numbers.frm");

            for (int cl = 0; cl < 3; cl++) //colors
            {
                for (int i = 0; i < 12; i++) // numbers
                {
                    _rects.emplace_back(Point(120*cl + i*9, 0), Size(9, 17));
                }
                // signs are 7 px wide
                _rects.emplace_back(Point(120*cl + 108 + 0*7, 0), Size(7, 17));
                _rects.emplace_back(Point(120*cl + 108 + 1*7, 0), Size(7, 17));
            }
        }

        void SmallCounter::setLength(unsigned int length)
        {
            _length = length;
        }

        unsigned int SmallCounter::length() const
        {
            return _length;
        }

        void SmallCounter::setNumber(signed int number)
        {
            _number = number;
            _numberText = std::to_string(number);
            if (_numberText.size() < _length)
            {
                _numberText.insert(0, _length - _numberText.size(), '0');
            }
        }

        signed int SmallCounter::number() const
        {
            return _number;
        }

        void SmallCounter::setColor(Color color)
        {
            switch(color)
            {
                case Color::WHITE:
                case Color::YELLOW:
                case Color::RED:
                    _color = color;
                    break;
            }
        }

        SmallCounter::Color SmallCounter::color() const
        {
            return _color;
        }

        void SmallCounter::setType(Type type)
        {
            _type = type;
        }

        SmallCounter::Type SmallCounter::type() const
        {
            return _type;
        }

        void SmallCounter::render(bool eggTransparency)
        {
            int pad = 0;
            if (_type == Type::SIGNED)
            {
                if (_number < 0) {
                    _sprite->renderCropped(position(), _rects.at(12*_color));
                } else {
                    _sprite->renderCropped(position(), _rects.at(13*_color));
                }
                pad = 6;
            }
            for (unsigned int i = 0; i < _length; i++)
            {
                int num = _numberText.at(i) - '0';
                switch (_color)
                {
                    case Color::YELLOW:
                        num += 14;
                        break;
                    case Color::RED:
                        num += 28;
                        break;
                    case Color::WHITE:
                    default:
                        break;
                }
                _sprite->renderCropped(position() + Point(pad + i*9, 0), _rects.at(num));
            }
        }

        bool SmallCounter::opaque(const Graphics::Point &pos)
        {
            return false;
        }
    }
}
