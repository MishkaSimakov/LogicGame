#include "MainMenuState.h"

MainMenuState::MainMenuState(Game &game) :
    BaseState(game), m_play_button({0.5, 0.5}, {0.25, 0.1}, "Start", game.getWindow())
{
    m_play_button.setCallback([&game]() {
        game.changeState<LevelState>(game);
    });
}

void MainMenuState::handleEvent(sf::Event e)
{
    m_play_button.handleEvent(e, m_game->getWindow());
}

void MainMenuState::update(sf::Time delta)
{}

void MainMenuState::render(sf::RenderTarget &renderer)
{
    renderer.clear(sf::Color::White);

    m_play_button.render(renderer);
}
