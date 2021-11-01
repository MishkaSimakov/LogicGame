#include "LevelState.h"

LevelState::LevelState(Game &game) : BaseState(game),
                                     m_documentation_block("hello world", "this is a long text about hello world",
                                                           game.getWindow().getSize().y) {
    m_static_logical_components.emplace_back(
            sf::Vector2f(500, 500),
            "hello world",
            &m_acting_logical_components
    );
}

void LevelState::handleEvent(sf::Event e) {
    m_documentation_block.handleEvent(e, m_game->getWindow());

    for (auto &static_component: m_static_logical_components) {
        static_component.handleEvent(e, m_game->getWindow());
    }
    for (auto &acting_component: m_acting_logical_components) {
        acting_component.handleEvent(e, m_game->getWindow());
    }
}

void LevelState::update(sf::Time delta) {}

void LevelState::render(sf::RenderTarget &renderer) {
    renderer.clear(sf::Color::White);

    m_documentation_block.render(renderer);

    for (auto &static_component: m_static_logical_components) {
        static_component.render(renderer);
    }
    for (auto &acting_component: m_acting_logical_components) {
        acting_component.render(renderer);
    }
}

