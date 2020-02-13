#include "../ResourceManager.h"
#include "../UI/BigCounter.h"

namespace Falltergeist
{
    namespace UI
    {
        BigCounter::BigCounter(int x, int y, unsigned int length) : BigCounter(Point(x, y), length)
        {
        }

        BigCounter::BigCounter(const Point& pos, unsigned int length) : Base(pos)
        {
            _length = length;
            _sprite = std::make_shared<Graphics::Sprite>("art/intrface/bignum.frm");
            for (int i = 0; i < 24; i++) {
                _rects.push_back({i*14, 0, 14, 24});
            }
        }

        BigCounter::~BigCounter()
        {
        }

        void BigCounter::setNumber(unsigned int number)
        {
            _number = number;
            _numberText = std::to_string(number);
            if (_numberText.size() < _length) {
                _numberText.insert(0, _length - _numberText.size(), '0');
            }
        }

        unsigned int BigCounter::number()
        {
            return _number;
        }

        void BigCounter::setColor(Color color)
        {
            switch (color) {
                case Color::WHITE:
                case Color::RED:
                    if (_color != color) {
                        _color = color;
                        //_textureOnDemand.reset();
                    }
                    break;
            }
        }

        BigCounter::Color BigCounter::color()
        {
            return _color;
        }

        void BigCounter::render(bool eggTransparency)
        {
            for (unsigned int i=0; i<_length;i++) {
                int num = _numberText.at(i)-'0';
                if (_color==Color::RED) {
                    num += 12;
                }
                SDL_Rect rect = _rects.at(num);
                _sprite->renderCropped(position().x() + i * 14, position().y(), rect.x, rect.y, rect.w, rect.h);
            }
        }

        bool BigCounter::opaque(const Point &pos)
        {
            return false;
        }
    }
}
