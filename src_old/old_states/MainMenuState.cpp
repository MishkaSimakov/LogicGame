#include "MainMenuState.h"

MainMenuState::MainMenuState(Game &game) :
        BaseState(game),
        m_play_button(
                {540, 310}, {200, 100}, L"Играть",
                gui::colors::white, "arial", 30,
                gui::colors::primary, 2, gui::colors::dark_primary
        ) {
    m_play_button.setCallback([&game]() {
        game.changeState<LevelState>(game);
    });
}

void MainMenuState::handleEvent(Event e) {
    m_play_button.handleEvent(e);
}

void MainMenuState::update(sf::Time delta) {}

void MainMenuState::render(sf::RenderTarget &renderer) {
    renderer.clear(sf::Color::White);

    m_play_button.render(renderer);
}
