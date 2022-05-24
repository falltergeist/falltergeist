#include "../State/Intro.h"
#include "../State/MainMenu.h"
#include "../State/Movie.h"
#include "../Game/Game.h"

namespace Falltergeist::State {
    Intro::Intro(
        std::shared_ptr<UI::IResourceManager> resourceManager,
        std::shared_ptr<Input::Mouse> mouse,
        std::shared_ptr<ILogger> logger
    ) : State(mouse), _resourceManager(resourceManager), _logger(logger) {
    }

    void Intro::init() {
        if (_initialized) {
            return;
        }
        State::init();

        setModal(true);
        setFullscreen(true);

        auto firstMovie = new Movie(mouse(), 1); // TODO replace raw integers with consts
        firstMovie->deactivateHandler().add([&](Event::State* event) {
          _onFirstMovieEnded();
        });
        Game::Game::getInstance()->pushState(firstMovie);
    }

    void Intro::_onFirstMovieEnded() {
        auto secondMovie = new Movie(mouse(), 17); // TODO replace raw integers with consts
        secondMovie->deactivateHandler().add([&](Event::State* event) {
            _onSecondMovieEnded();
        });
        Game::Game::getInstance()->pushState(secondMovie);
    }

    void Intro::_onSecondMovieEnded() {
        Game::Game::getInstance()->setState(new MainMenu(_resourceManager, mouse(), _logger));
    }
}
