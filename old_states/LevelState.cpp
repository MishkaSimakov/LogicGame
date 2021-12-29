#include "LevelState.h"

LevelState::LevelState(Game &game) :
        BaseState(game),
        m_documentation_block(
                ResourceHolder::get().levels.get("1").getTitle(),
                ResourceHolder::get().levels.get("1").getDescription(),
                (float) game.getWindow().getSize().y
        ) {
    gui::Simulation::get()->reset();

    m_static_components_block.addStaticComponent(And());
    m_static_components_block.addStaticComponent(Or());
}

void LevelState::handleEvent(Event e) {
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R) {
        gui::Simulation::get()->reset();
    }

    gui::Simulation::get()->handleEvent(e);
    m_documentation_block.handleEvent(e);
    m_static_components_block.handleEvent(e);
}

void LevelState::update(sf::Time delta) {}

void LevelState::render(sf::RenderTarget &renderer) {
    renderer.clear(sf::Color::White);

    gui::Simulation::get()->render(renderer);

    m_documentation_block.render(renderer);
    m_static_components_block.render(renderer);
}

