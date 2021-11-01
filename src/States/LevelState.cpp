#include "LevelState.h"

LevelState::LevelState(Game &game) :
        BaseState(game), m_r_rect({0, 0}, {200, (float) game.getWindow().getSize().y}, 10, gui::colors::gray,
                                  gui::RoundedRectangle::BOTTOM_RIGHT | gui::RoundedRectangle::TOP_RIGHT) {
    m_text.setFont(ResourceHolder::get().fonts.get("arial"));
    m_text.setString("Switch component");
    m_text.setPosition(10, 10);
    m_text.setCharacterSize(30);
    m_text.setFillColor(gui::colors::black);

    m_static_logical_components.emplace_back(
            sf::Vector2f(500, 500),
            "hello world",
            &m_acting_logical_components
    );
}

void LevelState::handleEvent(sf::Event e) {
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

    m_r_rect.render(renderer);
    renderer.draw(m_text);

    for (auto &static_component: m_static_logical_components) {
        static_component.render(renderer);
    }
    for (auto &acting_component: m_acting_logical_components) {
        acting_component.render(renderer);
    }
}

