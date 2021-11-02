#include "LevelState.h"

LevelState::LevelState(Game &game) : BaseState(game),
                                     m_documentation_block("Lorem ipsum", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer eget augue in turpis scelerisque dictum. Fusce nec lorem erat. Praesent sapien lectus, molestie at enim id, lobortis scelerisque lacus. Vestibulum ac sem eu tortor fermentum malesuada. Nulla egestas, enim non ultrices cursus, lorem diam facilisis tellus, a malesuada tellus arcu quis leo. Suspendisse a laoreet magna. Ut metus enim, feugiat eget condimentum in, tempus at nibh. Sed vel suscipit ipsum, id commodo purus. Pellentesque aliquam condimentum ipsum eget maximus. Nulla congue in ipsum ut tincidunt. Cras mollis leo a turpis volutpat, non gravida velit aliquam. Fusce tempus elit ac nisl ullamcorper ultrices eu at eros.",
                                                           (float) game.getWindow().getSize().y) {
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

