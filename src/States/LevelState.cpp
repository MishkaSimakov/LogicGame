#include "LevelState.h"

LevelState::LevelState(Game &game) :
        BaseState(game),
        m_documentation_block(
                ResourceHolder::get().levels.get("1").getTitle(),
                ResourceHolder::get().levels.get("1").getDescription(),
                (float) game.getWindow().getSize().y
        ) {
    m_static_logical_components.push_back(
            std::move(std::make_unique<gui::StaticLogicalComponent>(
                    sf::Vector2f(100, 100),
                    &m_simulation
            ))
    );
}

void LevelState::handleEvent(sf::Event e) {
    m_documentation_block.handleEvent(e, m_game->getWindow());
    m_simulation.handleEvent(e, m_game->getWindow());

    for (auto &component : m_static_logical_components) {
        component->handleEvent(e, m_game->getWindow());
    }
}

void LevelState::update(sf::Time delta) {}

void LevelState::render(sf::RenderTarget &renderer) {
    renderer.clear(sf::Color::White);

    m_documentation_block.render(renderer);
    m_simulation.render(renderer);

    for (auto &component : m_static_logical_components) {
        component->render(renderer);
    }
}

