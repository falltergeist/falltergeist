#include "../Game/Game.h"
#include "../Graphics/Movie.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/VertexArray.h"

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Movie::Movie() : _size(Size(640, 320)) {
        }

        const Size& Movie::size() const {
            return _size;
        }

        void Movie::loadFromSurface(SDL_Surface* surface)
        {
            _texture = std::make_unique<Texture>(
                Pixels(
                surface->pixels,
                Size(surface->w, surface->h),
                Pixels::Format::RGBA
                )
            );
        }

        void Movie::render(const Point& point)
        {
            if (!_texture) {
                return;
            }

            Game::getInstance()->renderer()->drawRectangle(Rectangle(point, _size), _texture.get());
        }
    }
}
