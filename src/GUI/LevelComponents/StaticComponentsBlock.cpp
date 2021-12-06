#include "StaticComponentsBlock.h"

gui::StaticComponentsBlock::StaticComponentsBlock() :
        m_background(
                {500, 600}, {680, 90}, 10, colors::gray
        ) {
    m_static_logical_components.push_back(
            std::move(std::make_unique<gui::StaticLogicalComponent>(
                    sf::Vector2f(510, 610),
                    "LogicalComponents/and"
            ))
    );
}

bool gui::StaticComponentsBlock::handleEvent(sf::Event e, const sf::RenderWindow &window) {
    for (auto &static_logical_component: m_static_logical_components) {
        if (static_logical_component->handleEvent(e, window))
            return true;
    }

    return false;
}

void gui::StaticComponentsBlock::render(sf::RenderTarget &renderer) {
    m_background.render(renderer);

    for (auto &static_logical_component: m_static_logical_components) {
        static_logical_component->render(renderer);
    }
}
