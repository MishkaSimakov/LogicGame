#include "LevelState.h"

LevelState::LevelState(Game &game) :
        BaseState(game),
        m_documentation_block(
                ResourceHolder::get().levels.get("1").getTitle(),
                ResourceHolder::get().levels.get("1").getDescription(),
                (float) game.getWindow().getSize().y
        ) {
    gui::Simulation::get()->reset();
}

void LevelState::handleEvent(sf::Event e) {
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R) {
        gui::Simulation::get()->reset();
    }

    gui::Simulation::get()->handleEvent(e, m_game->getWindow());
    m_documentation_block.handleEvent(e, m_game->getWindow());
    m_static_components_block.handleEvent(e, m_game->getWindow());
}

void LevelState::update(sf::Time delta) {}

void LevelState::render(sf::RenderTarget &renderer) {
    renderer.clear(sf::Color::White);

    gui::Simulation::get()->render(renderer);

    m_documentation_block.render(renderer);
    m_static_components_block.render(renderer);
}

